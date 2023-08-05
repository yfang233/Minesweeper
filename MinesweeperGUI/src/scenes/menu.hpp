#pragma once
#ifndef __MENU_H_
#define __MENU_H_

#include "display.hpp"

namespace minesweeper
{
	class menu : public gui::scene
	{
	public:
		explicit menu(display* d);
	};
}

#endif 