#pragma once
#ifndef __GAMING_H_
#define __GAMING_H_

#include "block.hpp"
#include "display.hpp"

namespace minesweeper
{
	class gaming : public gui::scene
	{
	public:
		explicit gaming(display* d);
	private:
		std::vector<block*> blocks_;
	};
}

#endif 