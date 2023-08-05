#include "block.hpp"
#include "game.hpp"
#include "display.hpp"
namespace minesweeper
{
	constexpr const char* texts[] = {"?","1","2","3","4","5","6","7","8"};

	block::block(int x, int y, int width, int height, int id, const Texture& flag, const Texture& mine, const Texture& boom) :gui::label(x, y, width, height, id), flag(flag), mine(mine), boom(boom)
	{
		alignment_ = gui::LABEL_MIDDLE_ALIGN;
		font_size_ = block_length - 8;
	}

	void block::draw()
	{

		DrawRectangleRounded({ static_cast<float>(x_),static_cast<float>(y_),static_cast<float>(width_),static_cast<float>(height_)}, 0.5, 5, background);
		switch (status)
		{
		case FLAG:
			DrawTextureV(flag, get_pos(), WHITE);
			break;
		case MINE:
			DrawTextureV(mine, get_pos(), WHITE);
			break;
		case BOOM:
			DrawTextureV(boom, get_pos(), WHITE);
			break;
		default:
			label::draw();
		}
	}

	void block::update(block_type type)
	{
		status = type;
		if(type>=1&&type<=8)
		{
			set_text(std::string(texts[type]));
			background = { LIGHTBLUE.r, LIGHTBLUE.g, LIGHTBLUE.b, 200 };
		}
		else if(type==QUESTION)
		{
			set_text(std::string(texts[0]));
		}
		else if (type == 0) 
		{
			background = { LIGHTBLUE.r, LIGHTBLUE.g, LIGHTBLUE.b, 50 };
		} else 
		{
			set_text(std::string());
		}
	}
}
