#pragma once
#ifndef __REPLAY_H_
#define __REPLAY_H_

#include "block.hpp"
#include "display.hpp"

namespace minesweeper
{
	class replay : public gui::scene
	{
	public:
		explicit replay(display* d);
	private:
		std::vector<block*> blocks_;
	};
}

#endif 