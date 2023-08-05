#pragma once
#ifndef __RANKLIST_H_
#define __RANKLIST_H_

#include <vector>
#include <string>
#include "game.hpp"
namespace minesweeper
{
	struct playermsg
	{
		unsigned long long score;
		std::string r_time = " ";
		static bool compare(const playermsg& msg1, const playermsg& msg2)
		{
			return msg1.score < msg2.score;
		}
	};

	class ranklist
	{
	public:
		explicit ranklist(game_difficulty difficulty);
		int savemsg(playermsg msg);
		std::string get_raw_text() const;
		constexpr static size_t MAX_RANK = 9;
		//make sure it matches the order of enums
		constexpr static const char* ranklist_filenames[DIFFICULTY_COUNT] = {
			"easy",
			"medium",
			"hard"
		};
	private:
		static std::string gettime();
		void readfile();
		void writefile() const;
		std::vector<playermsg> m_msg;
		std::string m_rankfile;
	};
}


#endif