#include "paused.hpp"

#include "exceptions.hpp"
#include "GUI/windlg.hpp"
#include "save.hpp"
#include "styles.hpp"
#include "utils.hpp"
using namespace util;
using namespace gui;
using namespace gui::util;
namespace minesweeper
{
	paused::paused(display* d) : scene(540, 690)
	{
		background_color = DEEPBLUE;
		auto* continue_button = new button(130, 60, 280, 90);
		auto* load_save_button = new button(130, 180, 280, 90);
		auto* create_save_button = new button(130, 300, 280, 90);
		auto* back_to_menu_button = new button(130, 420, 280, 90);
		auto* quit_game_button = new button(130, 540, 280, 90);
		add_widget(continue_button);
		add_widget(load_save_button);
		add_widget(create_save_button);
		add_widget(back_to_menu_button);
		add_widget(quit_game_button);
		continue_button->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		continue_button->set_text(std::string(u8"继续")).set_font(default_chinese_font, 64).set_font_size(50).set_font_color(LIGHTBLUE);
		load_save_button->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		load_save_button->set_text(std::string(u8"加载存档")).set_font(default_chinese_font, 64).set_font_size(50).set_font_color(LIGHTBLUE);
		create_save_button->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		create_save_button->set_text(std::string(u8"保存游戏")).set_font(default_chinese_font, 64).set_font_size(50).set_font_color(LIGHTBLUE);
		back_to_menu_button->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		back_to_menu_button->set_text(std::string(u8"回到主菜单")).set_font(default_chinese_font, 64).set_font_size(50).set_font_color(LIGHTBLUE);
		quit_game_button->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		quit_game_button->set_text(std::string(u8"退出游戏")).set_font(default_chinese_font, 64).set_font_size(50).set_font_color(LIGHTBLUE);
		continue_button->on_click([d](auto*)
			{
				d->switch_to(SCENE_GAMING);
				if (d->get_game()->status == GAME_INPROGRESS)
					d->get_game()->timer.start();
			});
		load_save_button->on_click([d](auto*)
			{
				std::vector<filename_filter> save_filter = { { "存档文件", "*.sav" } };
				const auto filename = windlg::ShowOpenFileDialog(save_filter);
				if (!filename.empty())
				{
					try
					{
						const auto s = save::load_from_file(filename.c_str());
						d->set_game(s.game_obj);
						s.game_obj->timer.start();
					}
					catch (file_corrupted_exception&)
					{
						windlg::ShowMessageBox("错误", "文件损坏");
						return;
					}
					catch (file_exception& e)
					{
						windlg::ShowMessageBox("错误", e.what());
						return;
					}
					d->display_scene(SCENE_GAMING);
				}
				
			});
		create_save_button->on_click([d](auto*)
			{
				std::vector<filename_filter> save_filter = { { "存档文件", "*.sav" } };
				auto filename = windlg::ShowSaveFileDialog(save_filter);
				if (!filename.empty())
				{
					if (!string_ends_with(filename, ".sav"))filename += ".sav";
					auto s = save::create_from_game(d->get_game(), filename.c_str());
				}
			});
		back_to_menu_button->on_click([d](auto*)
			{
				d->switch_to(SCENE_MENU);
			});
		quit_game_button->on_click([=](auto*)
			{
				form::get_instance().close();
			});
		

	}
}
