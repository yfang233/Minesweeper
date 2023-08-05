#pragma once
#ifndef __BLOCK_H_
#define __BLOCK_H_
#include "styles.hpp"
#include "game.hpp"
#include "GUI/widgets/label.hpp"
namespace minesweeper
{
	class block : public gui::label
	{
	public:
		explicit block(int x, int y, int width, int height, int id, const Texture& flag, const Texture& mine, const Texture& boom);
		void draw() override;
		void update(block_type type);
		block_type status = UNKNOWN;
		Color background = LIGHTBLUE;
		const Texture& flag;
		const Texture& mine;
		const Texture& boom;
	};
}

#endif