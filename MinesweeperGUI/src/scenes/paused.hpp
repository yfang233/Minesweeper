#pragma once
#ifndef __PAUSED_H_
#define __PAUSED_H_

#include "display.hpp"

namespace minesweeper
{
	class paused : public gui::scene
	{
	public:
		explicit paused(display* d);
	};
}

#endif 