#include "victory.hpp"
#include "ranklist_display.hpp"
#include "save.hpp"
#include "GUI/windlg.hpp"
#include "styles.hpp"
#include "utils.hpp"
using namespace util;
using namespace gui;
using namespace gui::util;
namespace minesweeper
{
	victory::victory(display* d, int rank) : scene(540, 840)
	{
		background_color = DEEPBLUE;
		auto* victory_title = new label(100, 40, 340, 100);
		add_widget(victory_title);
		victory_title->set_alignment(LABEL_MIDDLE_ALIGN).set_text("VICTORY!").set_font_size(60).set_font_color(GREEN);
		on_keyboard_keypressed(KEY_ESCAPE, [d, this](auto*)
			{
				d->display_scene(SCENE_MENU);
				if (d->get_game()->status == GAME_INPROGRESS)
					d->get_game()->timer.stop();
			});

		auto* create_replay_button = new button(90, 310, 360, 90);
		add_widget(create_replay_button);
		create_replay_button->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		create_replay_button->set_text(u8"保存回放").set_font(default_chinese_font, 64).set_font_color(LIGHTBLUE).set_font_size(50);
		create_replay_button->on_click([d](auto*)
			{
				std::vector<filename_filter> replay_filter = { { "回放文件", "*.replay" } };
				auto filename = windlg::ShowSaveFileDialog(replay_filter);
				if (!filename.empty())
				{
					if (!string_ends_with(filename, ".replay"))filename += ".replay";
					auto s = d->get_game()->save_recording(filename.c_str());
				}
			});
		auto* new_game_button = new button(90, 430, 360, 90);
		add_widget(new_game_button);
		new_game_button->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		new_game_button->set_text(u8"新游戏").set_font(default_chinese_font, 64).set_font_color(LIGHTBLUE).set_font_size(50);
		new_game_button->on_click([d](auto*)
			{
				d->switch_to(SCENE_LEVEL_SELECT);
			});
		auto* back_to_menu_button = new button(90, 550, 360, 90);
		add_widget(back_to_menu_button);
		back_to_menu_button->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		back_to_menu_button->set_text(u8"回到主菜单").set_font(default_chinese_font, 64).set_font_color(LIGHTBLUE).set_font_size(50);
		back_to_menu_button->on_click([d](auto*)
			{
				d->display_scene(SCENE_MENU);
			});

		auto* exit_button = new button(90, 670, 360, 90);
		add_widget(exit_button);
		exit_button->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		exit_button->set_text(u8"退出游戏").set_font(default_chinese_font, 64).set_font_color(LIGHTBLUE).set_font_size(50);
		exit_button->on_click([=](auto*)
			{
				form::get_instance().close();
			});

		auto* time_label = new button(90, 160, 160, 120);
		auto* rank_label = new button(290, 160, 160, 120);
		add_widget(time_label);
		add_widget(rank_label);
		const auto t = d->get_game()->timer.get_elapsed_time();
		time_label->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		time_label->set_text("\n" + std::to_string(t/1000) + "." + std::to_string((t/100)%10) + std::to_string((t/10)%10) + "s").set_font_size(40).set_font_color(LIGHTBLUE);
		if(rank!=0)
		{
			rank_ = std::to_string(rank);
		} else
		{
			rank_ = "--";
		}
		rank_label->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		rank_label->set_text("\n" + rank_).set_font_size(40).set_font_color(LIGHTBLUE);

		rank_label->on_click([=](auto*)
			{
				ranklist_args args = { SCENE_VICTORY, d->get_game()->get_difficulty() };
				switch (args.difficulty)
				{
					case DIFFICULTY_EASY:
					case DIFFICULTY_MEDIUM:
					case DIFFICULTY_HARD:
						d->display_scene(SCENE_RANKLIST, &args);
						break;
					default: 
						break;
				}
			});

		auto* time_text = new label(120, 170, 100, 40);
		add_widget(time_text);
		time_text->set_alignment(LABEL_MIDDLE_ALIGN).set_text(u8"用时").set_font(default_chinese_font,64).set_font_size(30).set_font_color(LIGHTBLUE);

		auto* rank_text = new label(320, 170, 100, 40);
		add_widget(rank_text);
		rank_text->set_alignment(LABEL_MIDDLE_ALIGN).set_text(u8"排名").set_font(default_chinese_font, 64).set_font_size(30).set_font_color(LIGHTBLUE);
	}

	
}
