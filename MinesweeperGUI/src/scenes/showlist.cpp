#include "showlist.hpp"
#include "save.hpp"
#include "styles.hpp"
#include "GUI/dir.hpp"
#include "ranklist_display.hpp"
using namespace gui;

namespace minesweeper
{
	showlist::showlist(display* d):scene(540,610)
	{
		background_color = DEEPBLUE;
		auto* easy_button = new button(130, 80, 280, 90);
		auto* mid_button = new button(130, 200, 280, 90);
		auto* hard_button = new button(130, 320, 280, 90);
		auto* back_button = new button(130, 440, 280, 90);
		add_widget(easy_button);
		add_widget(mid_button);
		add_widget(hard_button);
		add_widget(back_button);
		easy_button->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		easy_button->set_text(std::string(u8"初级")).set_font(default_chinese_font, 64).set_font_size(50).set_font_color(LIGHTBLUE);
		mid_button->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		mid_button->set_text(std::string(u8"中级")).set_font(default_chinese_font, 64).set_font_size(50).set_font_color(LIGHTBLUE);
		hard_button->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		hard_button->set_text(std::string(u8"高级")).set_font(default_chinese_font, 64).set_font_size(50).set_font_color(LIGHTBLUE);
		back_button->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		back_button->set_text(std::string(u8"返回")).set_font(default_chinese_font, 64).set_font_size(50).set_font_color(LIGHTBLUE);

		easy_button->on_click([=](auto*)
			{
				ranklist_args args = { SCENE_SHOWLIST, DIFFICULTY_EASY };
				d->display_scene( SCENE_RANKLIST, &args);
			});
		mid_button->on_click([=](auto*)
			{
				ranklist_args args = { SCENE_SHOWLIST, DIFFICULTY_MEDIUM };
				d->display_scene(SCENE_RANKLIST, &args);
			});
		hard_button->on_click([=](auto*)
			{
				ranklist_args args = { SCENE_SHOWLIST, DIFFICULTY_HARD };
				d->display_scene(SCENE_RANKLIST, &args);
			});
		back_button->on_click([d](auto*)
			{
				d->display_scene(SCENE_MENU);
			});
		on_keyboard_keypressed(KEY_ESCAPE, [=](auto*)
			{
				d->display_scene(SCENE_MENU);
			});
	};

}
