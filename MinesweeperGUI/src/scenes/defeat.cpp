#include "defeat.hpp"

#include "save.hpp"
#include "styles.hpp"

using namespace gui;

namespace minesweeper
{
	defeat::defeat(display* d) : scene(540, 510)
	{
		background_color = DEEPBLUE;
		auto* defeat_title = new label(100, 60, 340, 100);
		add_widget(defeat_title);
		defeat_title->set_alignment(LABEL_MIDDLE_ALIGN).set_text(u8"前面的地雷，下次再来探索吧！").set_font(default_chinese_font, 64).set_font_color(RED);

		auto* new_game_button = new button(130, 220, 280, 90);
		add_widget(new_game_button);
		new_game_button->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		new_game_button->set_text(u8"新游戏").set_font(default_chinese_font, 64).set_font_color(LIGHTBLUE).set_font_size(50);
		new_game_button->on_click([d](auto*)
		{
			d->switch_to(SCENE_LEVEL_SELECT);
		});
		auto* back_to_menu_button = new button(130, 340, 280, 90);
		add_widget(back_to_menu_button);
		back_to_menu_button->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		back_to_menu_button->set_text(u8"回到主菜单").set_font(default_chinese_font, 64).set_font_color(LIGHTBLUE).set_font_size(50);
		back_to_menu_button->on_click([d](auto*)
		{
			d->switch_to(SCENE_MENU);
		});
	}
}
