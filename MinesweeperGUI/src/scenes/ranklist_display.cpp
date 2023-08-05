#include "ranklist_display.hpp"
#include "save.hpp"
#include "styles.hpp"
#include "GUI/dir.hpp"
#include "ranklist.hpp"
using namespace gui;

namespace minesweeper
{
	ranklist_display::ranklist_display(display* d, ranklist_args args) :scene(720, 1080)
	{
		background_color = DEEPBLUE;
		auto* list = new label(0, 0, 720, 800);
		add_widget(list);
		list->set_alignment(LABEL_MIDDLE_ALIGN);
		auto* back_button = new button(200, 800, 320, 100);
		add_widget(back_button);
		back_button->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		back_button->set_text(std::string(u8"返回")).set_font(default_chinese_font, 64).set_font_size(50).set_font_color(LIGHTBLUE);
		ranklist rl(args.difficulty);
		if (const auto content = rl.get_raw_text(); !content.empty())
		{
			list->set_text(content).set_font_size(40).set_font_color(LIGHTBLUE);
		}
		else
		{
			auto* error = new label(0, 0, 720, 800);
			add_widget(error);
			error->set_alignment(LABEL_MIDDLE_ALIGN).set_text(std::string(u8"该难度还没有人通关哦！"));
			error->set_font(default_chinese_font, 64).set_font_color(LIGHTBLUE).set_font_size(50);
		}
		back_button->on_click([=](auto*)
			{
				d->switch_to(args.prev_scene);
			});
		on_keyboard_keypressed(KEY_ESCAPE, [=](auto*)
			{
				d->switch_to(args.prev_scene);
			});

	};

}
