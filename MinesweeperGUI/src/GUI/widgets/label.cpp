#include "GUI/widgets/label.hpp"
#include<string>
#include "GUI/dir.hpp"
namespace gui
{

	static int* CodepointRemoveDuplicates(const int* codepoints, int codepointCount, int* codepointsResultCount)
	{
		int codepointsNoDupsCount = codepointCount;
		int* codepointsNoDups = static_cast<int*>(calloc(codepointCount, sizeof(int)));
		memcpy(codepointsNoDups, codepoints, codepointCount * sizeof(int));

		// Remove duplicates
		for (int i = 0; i < codepointsNoDupsCount; i++)
		{
			for (int j = i + 1; j < codepointsNoDupsCount; j++)
			{
				if (codepointsNoDups[i] == codepointsNoDups[j])
				{
					for (int k = j; k < codepointsNoDupsCount; k++) codepointsNoDups[k] = codepointsNoDups[k + 1];

					codepointsNoDupsCount--;
					j--;
				}
			}
		}

		// NOTE: The size of codepointsNoDups is the same as original array but
		// only required positions are filled (codepointsNoDupsCount)

		*codepointsResultCount = codepointsNoDupsCount;
		return codepointsNoDups;
	}

	label::~label()
	{
		if (!fontname_.empty())
			UnloadFont(font_);
	}

	// As we are using float to store integers, there won't be any precision loss.
    void label::draw()
    {
		//check if font is valid and loaded
		if (font_.texture.id == 0)font_ = GetFontDefault();

		const int draw_spacing=(spacing_==-1?font_size_/font_.baseSize:spacing_);
		const auto text_size = MeasureTextEx(font_, text_.c_str(), font_size_, draw_spacing);
		float drawx;
		const float drawy = y_ + (height_ - text_size.y) / 2;

		if(background_color_.a!=0)
			DrawRectangleV(get_pos(), get_size(), background_color_);
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

    label& label::set_font(const char* filename, int resolution)
    {
		if (!fontname_.empty())
		{
			UnloadFont(font_);
		}
		if (strlen(filename) == 0)
		{
			fontname_ = "";
			font_ = GetFontDefault();
			SetTextureFilter(font_.texture, TEXTURE_FILTER_POINT);
			return *this;
		}
		fontname_ = util::dir::rel_to_abs(filename);
		int codepointCount = 0;
		int* codepoints = LoadCodepoints(text_.c_str(), &codepointCount);
		int codepointsNoDupsCount = 0;
		int* codepointsNoDups = CodepointRemoveDuplicates(codepoints, codepointCount, &codepointsNoDupsCount);
		UnloadCodepoints(codepoints);
		font_ = LoadFontEx(fontname_.c_str(), resolution, codepointsNoDups, codepointsNoDupsCount);
		free(codepointsNoDups);
		SetTextureFilter(font_.texture, TEXTURE_FILTER_BILINEAR);
		return *this;
    }

    label& label::set_font_size(int font_size)
    {
		font_size_ = font_size;
		return *this;
    }

    label& label::set_spacing(int spacing)
    {
		spacing_ = spacing;
		return *this;
    }

    label& label::set_font_color(Color color)
    {
		font_color_ = color;
		return *this;
    }

    label& label::set_alignment(label_alignment alignment)
    {
		alignment_ = alignment;
		return *this;
    }

    label& label::set_background_color(Color color)
    {
		background_color_ = color;
		return *this;
    }

	label& label::set_text(const std::string& text)
	{
		text_ = text;
		set_font(fontname_.c_str(), 64);
		return *this;
	}

	

}
