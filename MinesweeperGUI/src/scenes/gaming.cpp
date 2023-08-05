#include "gaming.hpp"

#include <iostream>

#include "styles.hpp"

#include "ranklist.hpp"

#include <iomanip>

#include "block.hpp"
#include "GUI/widgets/timer.hpp"

using namespace gui;

namespace minesweeper
{
	gaming::gaming(display* d) : scene(1280, 720)
	{
		// Be careful that rows is related to height, vice versa.
		auto* time = new timer();
		add_widget(time);
		const auto y = d->get_game()->rows * (block_length + block_spacing) + block_spacing;
		const auto x = d->get_game()->cols * (block_length + block_spacing) + block_spacing;
		width_ = x;
		height_ = y + 65;
		blocks_ = std::vector<block*>(d->get_game()->rows * d->get_game()->cols);
		background_color = DEEPDARKBLUE;
		for (int i = 0; i < d->get_game()->rows; i++)
		{
			for (int j = 0; j < d->get_game()->cols; j++)
			{
				auto* b = new block(block_spacing + j * (block_length + block_spacing), 65 + block_spacing + i * (block_length + block_spacing), block_length, block_length, i * d->get_game()->cols + j, d->get_texture(IMAGE_FLAG), d->get_texture(IMAGE_MINE), d->get_texture(IMAGE_BOOM));
				blocks_[i * d->get_game()->cols + j] = b;
				add_widget(b);
				b->on_click([this, b, d](event_args* args)
					{
						const auto* mouse_args = dynamic_cast<mouse_event_args*>(args);
						click_type t;
						if ((mouse_args->click_flags == (mouse_left | mouse_right)) || (mouse_args->keyleft == state_keydown && mouse_args->keyright == state_keydown))
						{
							t = CLK_DOUBLE;
						}
						else if (mouse_args->click_flags == mouse_left)
						{
							t = CLK_LEFT;
						}
						else if (mouse_args->click_flags == mouse_right)
						{
							t = CLK_RIGHT;
						}
						else
							return;
						auto result = d->get_game()->click_handler((b->id_ % d->get_game()->cols) + 1, (b->id_ / d->get_game()->cols) + 1, t);
						switch (result)
						{
						case CLK_LEFT:
						case CLK_DOUBLE:
						case CLK_FLAG:
						case CLK_CANCEL:
						case CLK_QUESTION:
							d->get_audio_device().play(AUDIO_CLICK);
						}
					});
				b->update(static_cast<block_type>(d->get_game()->usermap[i+1][j+1]));
			}
		}
		
		auto* time_label = new button(5, 5, 150, 60);
		add_widget(time_label);
		time_label->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(LIGHTBLUE);
		time_label->set_text(std::to_string(d->get_game()->timer.get_elapsed_time() / 1000) + "." + std::to_string((d->get_game()->timer.get_elapsed_time() / 100) % 10) + "s").set_font_size(40).set_font_color(BLACK);
		auto* mine_label = new button(x-155, 5, 150, 60);
		add_widget(mine_label);
		mine_label->set_alignment(LABEL_MIDDLE_ALIGN).set_background_color(LIGHTBLUE);
		mine_label->set_text("   " + std::to_string(d->get_game()->mine_left)).set_font_size(40).set_font_color(BLACK);
		auto* image = new imagebox(x - 140, 15);
		add_widget(image);
		image->set_texture(d->get_texture(IMAGE_MINE));
		time->on_tick(50, [=](auto*)
			{
				time_label->set_text(std::to_string(d->get_game()->timer.get_elapsed_time() / 1000) + "." + std::to_string((d->get_game()->timer.get_elapsed_time() / 100) % 10) + "s");
				mine_label->set_text("   " + std::to_string(d->get_game()->mine_left));

			});
		on_keyboard_keypressed(KEY_ESCAPE,[d,this](auto*)
		{
				d->switch_to(SCENE_PAUSED);
				if(d->get_game()->status == GAME_INPROGRESS)
					d->get_game()->timer.stop();
			
		});
		d->get_game()->update_hook = [this, d](int x, int y, block_type type)
		{
			if (d->get_game()->is_recording()) 
				d->get_game()->get_recording().add_timepoint({ d->get_game()->timer.get_elapsed_time(),x,y,static_cast<char>(type) });
			blocks_[(x - 1) * d->get_game()->cols + (y - 1)]->update(type);
		};
		d->get_game()->lose_hook = [=](game& _)
		{
			d->get_audio_device().play(AUDIO_BOOM);
			auto* deadtime = new timer();
			add_widget(deadtime);
			deadtime->on_tick(1000, [=](auto*)
				{
					std::cout << "hit mine, lose!" << std::endl;
					d->display_scene(SCENE_DEFEAT);
					deadtime->enabled = false;

				});
		};
		d->get_game()->win_hook = [=](const game& _)
		{
			playermsg m_msg = playermsg();
			m_msg.score = _.timer.get_elapsed_time();
			auto rank = 0;
			if(_.get_difficulty()!=DIFFICULTY_CUSTOM)
			{
				ranklist m_ranklist = ranklist(_.get_difficulty());
				rank = m_ranklist.savemsg(m_msg);
			}
			std::cout << "win!" << _.timer.get_elapsed_time() << std::endl;
			d->display_scene(SCENE_VICTORY,&rank);
		};
	}
}
