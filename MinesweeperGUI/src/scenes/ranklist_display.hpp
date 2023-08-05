#pragma once
#ifndef __RANKLIST_DISPLAY_H_
#define __RANKLIST_DISPLAY_H_

#include "display.hpp"

namespace minesweeper
{
	struct ranklist_args
	{
		game_scenes prev_scene;
		game_difficulty difficulty;
	};
	class ranklist_display : public gui::scene
	{
	public:
		explicit ranklist_display(display* d, ranklist_args args);
	};
}


#endif