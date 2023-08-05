#pragma once
#ifndef __LABEL_H_
#define __LABEL_H_
#include<string>

#include "GUI/widget.hpp"
namespace gui
{
	enum label_alignment
	{
		LABEL_LEFT_ALIGN,
		LABEL_MIDDLE_ALIGN,
		LABEL_RIGHT_ALIGN
	};
	class label : public widget
	{
	public:
		explicit label(int x, int y, int width, int height, int id = -1) : widget(x, y, width, height, id) { }
		~label() override;
		label& set_font(const char* filename, int resolution);
		label& set_font_size(int font_size);
		label& set_spacing(int spacing);
		label& set_font_color(Color color);
		label& set_alignment(label_alignment alignment);
		label& set_background_color(Color color);
		label& set_text(const std::string& text);

	protected:
		void draw() override;
		std::string text_;
		Font font_ = Font{};
		int font_size_ = 30;
		int spacing_ = -1; //-1 for default
		Color font_color_ = BLACK;
		Color background_color_ = BLANK;
		label_alignment alignment_ = LABEL_LEFT_ALIGN;
		std::string fontname_;
	};
}

#endif