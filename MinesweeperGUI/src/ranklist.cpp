#define _CRT_SECURE_NO_WARNINGS
#include "ranklist.hpp"
#include <ctime>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <string>
#include "GUI\dir.hpp"
#include "exceptions.hpp"
namespace minesweeper
{

	ranklist::ranklist(game_difficulty difficulty)
	{
		if(difficulty<0 || difficulty >= DIFFICULTY_COUNT) throw std::exception("unknown game_difficulty");
		m_rankfile = ranklist_filenames[difficulty];
		readfile();
	}

	int ranklist::savemsg(playermsg msg)
	{
		int rank = 0;

		msg.r_time = gettime();

		m_msg.push_back(msg);
		std::sort(m_msg.begin(), m_msg.end(), playermsg::compare);

		for (int i = 0; i < m_msg.size() && i < MAX_RANK; i++)
		{
			if (m_msg[i].score == msg.score)
			{
				rank = i + 1;
			}
		}
		writefile();
		return rank;
	}

	std::string ranklist::get_raw_text() const
	{
		std::ifstream infile;
		infile.open(gui::util::dir::rel_to_abs(m_rankfile.c_str()), std::ios::in);
		if (!infile.is_open()) throw file_exception("error opening ranklist files");
		std::string buffer = { 0 };
		std::string text;
		while (!infile.eof())
		{
			std::getline(infile, buffer);
			text += buffer;
			text.push_back('\n');
		}
		text.pop_back();
		infile.close();
		return text;
	}

	std::string ranklist::gettime()
	{
		const time_t now = time(0);

		const tm* ltm = localtime(&now);

		std::stringstream sstream;

		sstream << ltm->tm_year + 1900 - 2000 << "-";
		sstream << ((ltm->tm_mon + 1 >= 10) ? "" : "0") << ltm->tm_mon + 1 << "-";
		sstream << ((ltm->tm_mday >= 10) ? "" : "0") << ltm->tm_mday << "_";
		sstream << ((ltm->tm_hour >= 10) ? "" : "0") << ltm->tm_hour << ":";
		sstream << ((ltm->tm_min >= 10) ? "" : "0") << ltm->tm_min;

		return sstream.str();
	}

	void ranklist::readfile()
	{
		std::ifstream infile;

		infile.open(gui::util::dir::rel_to_abs(m_rankfile.c_str()), std::ios::in);

		if (!infile)
		{
			std::ofstream os;
			os.open(gui::util::dir::rel_to_abs(m_rankfile.c_str()));

			if (!os)
			{
				throw file_exception("Failed to open the file");
			}
			os.close();
		}
		else
		{
			std::string line;
			std::stringstream stream;
			playermsg msg;

			while (std::getline(infile, line))
			{
				stream.clear();
				stream.str(line);
				int id;
				char buf;
				stream >> id >> buf;
				if (buf != '.') throw file_corrupted_exception();
				double tmp;
				stream >> tmp;
				msg.score = tmp * 1000;
				stream >> buf;
				if (buf != 's') throw file_corrupted_exception();
				stream >> msg.r_time;
				m_msg.push_back(msg);
			}
			std::sort(m_msg.begin(), m_msg.end(), playermsg::compare);
		}
		infile.close();
	}

	void ranklist::writefile() const
	{
		std::ofstream outfile;

		outfile.open(gui::util::dir::rel_to_abs(m_rankfile.c_str()), std::ios::out);

		if (!outfile)
		{
			throw file_exception("open outfile failed");
		}
		for (auto i=1;i<=std::min(m_msg.size(),MAX_RANK);i++)
		{
			std::stringstream temp;
			temp << std::setiosflags(std::ios::fixed) << std::setprecision(3) << m_msg[i-1].score / 1000.0 << "s";
			outfile << i << ".  " << temp.str() << "  " << m_msg[i-1].r_time << std::endl;
		}
		outfile.close();
	}
}
