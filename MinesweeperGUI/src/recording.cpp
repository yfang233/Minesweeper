#include "recording.hpp"
#include<filesystem>
#include<fstream>

#include "exceptions.hpp"
using namespace std;
#define BINARY_WRITE(file,ptr) \
	file.write(reinterpret_cast<const char*>(ptr),sizeof(*(ptr)))
#define BINARY_READ(file,ptr) \
	file.read(reinterpret_cast<char*>(ptr),sizeof(*(ptr)))
namespace minesweeper
{
	fstream& operator>>(fstream& file, recording_timepoint& point)
	{
		BINARY_READ(file, &point.timepoint);
		BINARY_READ(file, &point.rows);
		BINARY_READ(file, &point.cols);
		BINARY_READ(file, &point.type);
		return file;
	}

	fstream& operator<<(fstream& file, const recording_timepoint& point)
	{
		BINARY_WRITE(file, &point.timepoint);
		BINARY_WRITE(file, &point.rows);
		BINARY_WRITE(file, &point.cols);
		BINARY_WRITE(file, &point.type);
		return file;
	}

	recording::recording(const game& g)
	{
		rows_ = g.rows;
		cols_ = g.cols;
		map = new char*[rows_];
		for (int i = 0; i < rows_; i++)
		{
			map[i] = new char[cols_];
		}
	}

	recording::recording(const char* filename)
	{
		const filesystem::path p(filename);
		fstream file(p,ios::in|ios::binary);
		for (const unsigned char i : recording_magic_num)
		{
			unsigned char buf;
			BINARY_READ(file, &buf);
			if (buf != i)throw file_corrupted_exception();
		}
		{
			unsigned char ver;
			BINARY_READ(file, &ver);
			if (ver > current_recording_version)throw file_exception("higher version of recording not supported");
		}
		{
			int rows;
			BINARY_READ(file, &rows);
			rows_ = rows;
		}
		{
			int cols;
			BINARY_READ(file, &cols);
			cols_ = cols;
		}
		while(!file.eof())
		{
			recording_timepoint point;
			file >> point;
			data.emplace_back(point);
		}
		file.close();
	}

	recording::~recording()
	{
		for (int i = 0;i<rows_;i++)
		{
			delete[] map[i];
		}
		delete[] map;
	}

	void recording::add_timepoint(recording_timepoint timepoint)
	{
		data.emplace_back(timepoint);
	}

	void recording::save(const char* filename) const
	{
		const filesystem::path p(filename);
		fstream file(p, ios::out | ios::trunc | ios::binary);
		file.write(reinterpret_cast<const char*>(recording_magic_num), sizeof(recording_magic_num));
		BINARY_WRITE(file, &current_recording_version);
		BINARY_WRITE(file, &rows_);
		BINARY_WRITE(file, &cols_);

		for (auto& i : data)
		{
			file << i;
		}
		file.close();
	}

}
