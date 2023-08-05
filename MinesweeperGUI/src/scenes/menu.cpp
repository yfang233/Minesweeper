#include "menu.hpp"
#include "save.hpp"
#include "GUI/windlg.hpp"
#include "styles.hpp"
#include "exceptions.hpp"
using namespace gui;

namespace minesweeper
{
	menu::menu(display* d) : scene(540, 800)
	{
		background_color = DEEPBLUE;
		auto* b1 = new button(130, 200, 280, 90);
		auto* b2 = new button(130, 320, 280, 90);
		auto* b3 = new button(130, 440, 280, 90);
		auto* b4 = new button(130, 560, 280, 90);
		auto* b5 = new button(130, 680, 280, 90);
		add_widget(b1);
		add_widget(b2);
		add_widget(b3);
		add_widget(b4);
		add_widget(b5);
		b1->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		b1->set_text(std::string(u8"新游戏")).set_font(default_chinese_font, 64).set_font_size(50).set_font_color(LIGHTBLUE);
		b2->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		b2->set_text(std::string(u8"加载游戏")).set_font(default_chinese_font, 64).set_font_size(50).set_font_color(LIGHTBLUE);
		b3->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		b3->set_text(std::string(u8"加载回放")).set_font(default_chinese_font, 64).set_font_size(50).set_font_color(LIGHTBLUE);
		b4->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		b4->set_text(std::string(u8"查看排行榜")).set_font(default_chinese_font, 64).set_font_size(50).set_font_color(LIGHTBLUE);
		b5->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		b5->set_text(std::string(u8"退出游戏")).set_font(default_chinese_font, 64).set_font_size(50).set_font_color(LIGHTBLUE);
		b1->on_click([d](auto*)
			{
				d->display_scene(SCENE_LEVEL_SELECT);
			});
		b2->on_click([d](auto*)
			{
				std::vector<filename_filter> save_filter = {{ "存档文件", "*.sav" }};
				const auto filename = windlg::ShowOpenFileDialog(save_filter);
				if(!filename.empty())
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
		b3->on_click([d](auto*)
			{
				std::vector<filename_filter> save_filter = {{ "回放文件", "*.replay" }};
				const auto filename = windlg::ShowOpenFileDialog(save_filter);

				if(!filename.empty())
				{
					try
					{
						auto* g = game::load_from_recording(filename.c_str());
						d->set_game(g);
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
					d->display_scene(SCENE_REPLAY);
				}
			});
		b4->on_click([=](auto*)
			{
				d->display_scene(SCENE_SHOWLIST);
			});
		b5->on_click([=](auto*)
			{
				form::get_instance().close();
			});
		auto* title = new label(130, 50, 280, 100);
		add_widget(title);
		title->set_text(std::string("MINESWEEPER")).set_alignment(LABEL_MIDDLE_ALIGN).set_font_size(60).set_font_color(PURPLE);

	}
}
