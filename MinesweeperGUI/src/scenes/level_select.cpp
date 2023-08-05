#include "level_select.hpp"
#include<iostream>
#include "styles.hpp"
#include "ranklist.hpp"
#include "GUI/clock.hpp"
using namespace gui;

namespace minesweeper
{
	level_select::level_select(display* d) : scene(1200, 800)
	{
		background_color = DEEPBLUE;

		auto* basic_level = new button(750, 200, 400, 150);
		auto* mid_level = new button(750, 400, 400, 150);
		auto* advanced_level = new button(750,600,400,150);
		add_widget(basic_level);
		add_widget(mid_level);
		add_widget(advanced_level);
		basic_level->set_alignment(LABEL_LEFT_ALIGN).set_background_color(DEEPDARKBLUE);
		basic_level->set_text(std::string(u8"   初级")).set_font(default_chinese_font,64).set_font_size(50).set_font_color(LIGHTBLUE);
		mid_level->set_alignment(LABEL_LEFT_ALIGN).set_background_color(DEEPDARKBLUE);
		mid_level->set_text(std::string(u8"   中级")).set_font(default_chinese_font,64).set_font_size(50).set_font_color(LIGHTBLUE);
		advanced_level->set_alignment(LABEL_LEFT_ALIGN).set_background_color(DEEPDARKBLUE);
		advanced_level->set_text(std::string(u8"   高级")).set_font(default_chinese_font,64).set_font_size(50).set_font_color(LIGHTBLUE);

		
		
		auto* rows_num = new button(280, 200, 150, 150);
		auto* cols_num = new button(280, 400, 150, 150);
		auto* mine_num = new button(280, 600, 150, 150);
		add_widget(cols_num);
		add_widget(rows_num);
		add_widget(mine_num);
		cols_num->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		cols_num->set_text(cols_).set_font_size(50).set_font_color(LIGHTBLUE);
		rows_num->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		rows_num->set_text(rows_).set_font_size(50).set_font_color(LIGHTBLUE);
		mine_num->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		mine_num->set_text(mine_count_).set_font_size(50).set_font_color(LIGHTBLUE);

		auto* plus_sign1 = new button(480, 245, 60, 60);
		auto* plus_sign2 = new button(480, 445, 60, 60);
		auto* plus_sign3 = new button(480, 645, 60, 60);
		add_widget(plus_sign1);
		add_widget(plus_sign2);
		add_widget(plus_sign3);
		plus_sign1->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		plus_sign1->set_text(std::string("+")).set_font_size(50).set_font_color(LIGHTBLUE);
		plus_sign2->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		plus_sign2->set_text(std::string("+")).set_font_size(50).set_font_color(LIGHTBLUE);
		plus_sign3->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		plus_sign3->set_text(std::string("+")).set_font_size(50).set_font_color(LIGHTBLUE);


		plus_sign1->on_click([=](auto*)
		{
			add_rows(1);
			rows_num->set_text(rows_);
		});
		plus_sign2->on_click([=](auto*)
		{
			add_cols(1);
			cols_num->set_text(cols_);
		});
		plus_sign3->on_click([=](auto*)
		{
			add_mine_count(1);
			mine_num->set_text(mine_count_);
		});

		auto* plus10_sign1 = new button(570, 245, 100, 60);
		auto* plus10_sign2 = new button(570, 445, 100, 60);
		auto* plus10_sign3 = new button(570, 645, 100, 60);
		add_widget(plus10_sign1);
		add_widget(plus10_sign2);
		add_widget(plus10_sign3);
		plus10_sign1->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		plus10_sign1->set_text(std::string("+10")).set_font_size(50).set_font_color(LIGHTBLUE);
		plus10_sign2->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		plus10_sign2->set_text(std::string("+10")).set_font_size(50).set_font_color(LIGHTBLUE);
		plus10_sign3->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		plus10_sign3->set_text(std::string("+10")).set_font_size(50).set_font_color(LIGHTBLUE);

		plus10_sign1->on_click([=](auto*)
		{
			add_rows(10);
			rows_num->set_text(rows_);
		});
		plus10_sign2->on_click([=](auto*)
		{
			add_cols(10);
			cols_num->set_text(cols_);
		});
		plus10_sign3->on_click([=](auto*)
		{
			add_mine_count(10);
			mine_num->set_text(mine_count_);
		});

		auto* minus_sign1 = new button(170, 245, 60, 60);
		auto* minus_sign2 = new button(170, 445, 60, 60);
		auto* minus_sign3 = new button(170, 645, 60, 60);
		add_widget(minus_sign1);
		add_widget(minus_sign2);
		add_widget(minus_sign3);
		minus_sign1->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		minus_sign1->set_text(std::string("-")).set_font_size(50).set_font_color(LIGHTBLUE);
		minus_sign2->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		minus_sign2->set_text(std::string("-")).set_font_size(50).set_font_color(LIGHTBLUE);
		minus_sign3->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		minus_sign3->set_text(std::string("-")).set_font_size(50).set_font_color(LIGHTBLUE);

		minus_sign1->on_click([=](auto*)
		{
			add_rows(-1);
			rows_num->set_text(rows_);
		});
		minus_sign2->on_click([=](auto*)
		{
			add_cols(-1);
			cols_num->set_text(cols_);
		});
		minus_sign3->on_click([=](auto*)
		{
			add_mine_count(-1);
			mine_num->set_text(mine_count_);
		});
		
		auto* minus10_sign1 = new button(40, 245, 100, 60);
		auto* minus10_sign2 = new button(40, 445, 100, 60);
		auto* minus10_sign3 = new button(40, 645, 100, 60);
		add_widget(minus10_sign1);
		add_widget(minus10_sign2);
		add_widget(minus10_sign3);
		minus10_sign1->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		minus10_sign1->set_text(std::string("-10")).set_font_size(50).set_font_color(LIGHTBLUE);
		minus10_sign2->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		minus10_sign2->set_text(std::string("-10")).set_font_size(50).set_font_color(LIGHTBLUE);
		minus10_sign3->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		minus10_sign3->set_text(std::string("-10")).set_font_size(50).set_font_color(LIGHTBLUE);

		minus10_sign1->on_click([=](auto*)
		{
			add_rows(-10);
			rows_num->set_text(rows_);
		});
		minus10_sign2->on_click([=](auto*)
		{
			add_cols(-10);
			cols_num->set_text(cols_);
		});
		minus10_sign3->on_click([=](auto*)
		{
			add_mine_count(-10);
			mine_num->set_text(mine_count_);
		});

		auto* start_button = new button(870, 40, 280, 100);
		add_widget(start_button);
		start_button->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		start_button->set_text(std::string(u8"开始游戏→")).set_font(default_chinese_font,64).set_font_size(40).set_font_color(LIGHTBLUE);

		auto* back_button = new button(70, 40, 200, 100);
		add_widget(back_button);
		back_button->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(DEEPDARKBLUE);
		back_button->set_text(std::string(u8"←返回")).set_font(default_chinese_font,64).set_font_size(40).set_font_color(LIGHTBLUE);

		back_button->on_click([d](auto*)
			{
				d->switch_to(SCENE_MENU);
			});

		start_button->on_click([d,this](auto*)
			{
				auto* g = new game(std::stoi(rows_),std::stoi(cols_),std::stoi(mine_count_));
				g->enable_recording();
				d->set_game(g);
				d->display_scene(SCENE_GAMING);
			});

		basic_level->on_click([=](auto*)
			{
				cols_ = "9";
				rows_ = "9";
				mine_count_ = "10";
				cols_num->set_text(cols_);
				rows_num->set_text(rows_);
				mine_num->set_text(mine_count_);
			});
		mid_level->on_click([=](auto*)
			{
				cols_ = "16";
				rows_ = "16";
				mine_count_ = "40";
				cols_num->set_text(cols_);
				rows_num->set_text(rows_);
				mine_num->set_text(mine_count_);
			});
		advanced_level->on_click([=](auto*)
			{
				cols_ = "30";
				rows_ = "16";
				mine_count_ = "99";
				cols_num->set_text(cols_);
				rows_num->set_text(rows_);
				mine_num->set_text(mine_count_);
			});

		auto* rows_label = new label(305, 195, 100, 60);
		auto* cols_label = new label(305, 395, 100, 60);
		auto* mine_label = new label(305, 595, 100, 60);
		add_widget(rows_label);
		add_widget(cols_label);
		add_widget(mine_label);
		rows_label->set_alignment(LABEL_MIDDLE_ALIGN).set_text(u8"行数").set_font(default_chinese_font,64).set_font_size(30).set_font_color(LIGHTBLUE);
		cols_label->set_alignment(LABEL_MIDDLE_ALIGN).set_text(u8"列数").set_font(default_chinese_font, 64).set_font_size(30).set_font_color(LIGHTBLUE);
		mine_label->set_alignment(LABEL_MIDDLE_ALIGN).set_text(u8"雷数").set_font(default_chinese_font, 64).set_font_size(30).set_font_color(LIGHTBLUE);


		auto* tag1 = new label(980, 220, 100, 60);
		auto* tag2 = new label(980, 420, 100, 60);
		auto* tag3 = new label(980, 620, 100, 60);
		add_widget(tag1);
		add_widget(tag2);
		add_widget(tag3);
		tag1->set_alignment(LABEL_MIDDLE_ALIGN).set_text(u8"9×9").set_font_size(40).set_font_color(LIGHTBLUE);
		tag2->set_alignment(LABEL_MIDDLE_ALIGN).set_text(u8"16×16").set_font_size(40).set_font_color(LIGHTBLUE);
		tag3->set_alignment(LABEL_MIDDLE_ALIGN).set_text(u8"16×30").set_font_size(40).set_font_color(LIGHTBLUE);

		auto* image1 = new imagebox(975, 280);
		auto* image2 = new imagebox(970, 480);
		auto* image3 = new imagebox(970, 680);
		add_widget(image1);
		add_widget(image2);
		add_widget(image3);
		image1->set_texture(d->get_texture(IMAGE_MINE)).set_background_color(LIGHTBLUE);
		image2->set_texture(d->get_texture(IMAGE_MINE)).set_background_color(LIGHTBLUE);
		image3->set_texture(d->get_texture(IMAGE_MINE)).set_background_color(LIGHTBLUE);

		auto* tag4 = new label(1000, 273, 100, 60);
		auto* tag5 = new label(1000, 473, 100, 60);
		auto* tag6 = new label(1000, 673, 100, 60);
		add_widget(tag4);
		add_widget(tag5);
		add_widget(tag6);
		tag4->set_alignment(LABEL_MIDDLE_ALIGN).set_text(u8"×10").set_font_size(40).set_font_color(LIGHTBLUE);
		tag5->set_alignment(LABEL_MIDDLE_ALIGN).set_text(u8"×40").set_font_size(40).set_font_color(LIGHTBLUE);
		tag6->set_alignment(LABEL_MIDDLE_ALIGN).set_text(u8"×99").set_font_size(40).set_font_color(LIGHTBLUE);

		on_keyboard_keypressed(KEY_ESCAPE, [d, this](auto*)
			{
				d->display_scene(SCENE_MENU);
			});
	}	

	void level_select::add_rows(int r)
	{
		int temp = std::stoi(rows_);
		temp += r;
		if(temp > 24)
		{
			temp = 24;
		}
		if(temp < 9)
		{
			temp = 9;
		}
		rows_ = std::to_string(temp);
	}

	void level_select::add_cols(int c)
	{
		int temp = std::stoi(cols_);
		temp += c;
		if (temp > 30)
		{
			temp = 30;
		}
		if (temp < 9)
		{
			temp = 9;
		}
		cols_ = std::to_string(temp);
	}

	void level_select::add_mine_count(int m)
	{
		int temp = std::stoi(mine_count_);
		temp += m;
		if (temp > std::stoi(cols_)*std::stoi(rows_)-1)
		{
			temp = std::stoi(cols_) * std::stoi(rows_) - 1;
		}
		if (temp < 2)
		{
			temp = 2;
		}
		mine_count_ = std::to_string(temp);
	}


}