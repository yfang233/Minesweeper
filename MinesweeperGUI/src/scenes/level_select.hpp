#pragma once
#ifndef __LEVEL_SELECT_H_
#define __LEVEL_SELECT_H_

#include "display.hpp"

namespace minesweeper
{
	class level_select : public gui::scene
	{
	public:
		explicit level_select(display* d);
		void add_rows(int r);
		void add_cols(int c);
		void add_mine_count(int m);

	protected:
		std::string rows_ = "9";
		std::string cols_ = "9";
		std::string mine_count_ = "10";
	};
}

#endif