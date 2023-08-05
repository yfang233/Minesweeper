#include "GUI/widgets/button.hpp"
#include<iostream>
#include "raylib/raylib.h"

using namespace std;
namespace gui {
	void button::draw()
	{
		//check if font is valid and loaded
		if (font_.texture.id == 0)font_ = GetFontDefault();

		const int draw_spacing = (spacing_ == -1 ? font_size_ / font_.baseSize : spacing_);
		const auto text_size = MeasureTextEx(font_, text_.c_str(), font_size_, draw_spacing);
		float drawx;
		const float drawy = y_ + (height_ - text_size.y) / 2;

		if (background_color_.a != 0)
			//DrawRectangleV(get_pos(), get_size(), background_color_);
			DrawRectangleRounded({ static_cast<float>(x_),static_cast<float>(y_),static_cast<float>(width_),static_cast<float>(height_) }, 0.25, 5, background_color_);
		switch (alignment_)
		{
		case LABEL_LEFT_ALIGN:
			DrawTextEx(font_, text_.c_str(), { static_cast<float>(x_),drawy }, font_size_, draw_spacing, font_color_);
			break;
		case LABEL_MIDDLE_ALIGN:
			drawx = x_ + (width_ - text_size.x) / 2;
			DrawTextEx(font_, text_.c_str(), { drawx,drawy }, font_size_, draw_spacing, font_color_);
			break;
		case LABEL_RIGHT_ALIGN:
			drawx = x_ + width_ - text_size.x;
			DrawTextEx(font_, text_.c_str(), { drawx,drawy }, font_size_, draw_spacing, font_color_);
			break;
		}
		//TODO
	}


}