#pragma once
#ifndef __SHOWLIST_H_
#define __SHOWLIST_H_

#include "display.hpp"

namespace minesweeper
{
	class showlist : public gui::scene
	{
	public:
		explicit showlist(display* d);
	};
}

#endif 