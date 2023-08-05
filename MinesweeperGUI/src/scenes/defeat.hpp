#pragma once
#ifndef __DEFEAT_H_
#define __DEFEAT_H_

#include "display.hpp"

namespace minesweeper
{
	class defeat : public gui::scene
	{
	public:
		explicit defeat(display* d);
	};
}

#endif 