#pragma once
#ifndef __VICTORY_H_
#define __VICTORY_H_

#include "display.hpp"

namespace minesweeper
{
	class victory : public gui::scene
	{
	public:
		explicit victory(display* d, int rank = 0);

	private:
		std::string time_ = "0";
		std::string rank_ = "--";
	};
}

#endif 