#pragma once
#ifndef __IMAGEBOX_H_
#define __IMAGEBOX_H_

#include "GUI/widget.hpp"

namespace gui
{
	class imagebox : public widget
	{
	public:
		explicit imagebox(int x,int y, int id = -1) : widget(x,y,0,0,id) {}
		imagebox& set_img(const Image* img);
		void draw() override;
		imagebox& set_background_color(Color color);
		imagebox& set_texture(const Texture& texture);
	private:
		Color background_color_ = BLANK;
		Texture texture_={0,0,0,0,0};
	};
}

#endif