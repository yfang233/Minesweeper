#include "GUI/widgets/imagebox.hpp"
#include "raylib/raylib.h"
namespace gui
{

	imagebox& imagebox::set_img(const Image* img)
	{
		resize(img->width, img->height);
		texture_ = LoadTextureFromImage(*img);
		return *this;
	}

	void imagebox::draw()
	{
		if (background_color_.a != 0)
			DrawRectangleV(get_pos(), get_size(), background_color_);
		if (texture_.id==0)return;
		DrawTextureV(texture_,get_pos(), WHITE);
	}

	imagebox& imagebox::set_background_color(Color color)
	{
		background_color_ = color;
		return *this;
	}

	imagebox& imagebox::set_texture(const Texture& texture)
	{
		resize(texture.width, texture.height);
		texture_ = texture;
		return *this;
	}
}
