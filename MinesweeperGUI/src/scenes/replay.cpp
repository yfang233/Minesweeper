#include "replay.hpp"

#include "exceptions.hpp"
#include "save.hpp"
#include "GUI/windlg.hpp"
#include "styles.hpp"

using namespace gui;

namespace minesweeper
{
	replay::replay(display* d) : scene(1280, 720)
	{
		background_color = DEEPDARKBLUE;
		if (d->get_game()->status != GAME_RECORDING)
			throw game_exception("you have to load a recording before displaying it");
		const auto y = d->get_game()->rows * (block_length + block_spacing) + block_spacing;
		const auto x = d->get_game()->cols * (block_length + block_spacing) + block_spacing;
		width_ = x;
		height_ = y;
		blocks_ = std::vector<block*>(d->get_game()->rows * d->get_game()->cols);
		for (int i = 0; i < d->get_game()->rows; i++)
		{
			for (int j = 0; j < d->get_game()->cols; j++)
			{
				auto* b = new block(block_spacing + j * (block_length + block_spacing), block_spacing + i * (block_length + block_spacing), block_length, block_length, i * d->get_game()->rows + j, d->get_texture(IMAGE_FLAG), d->get_texture(IMAGE_MINE), d->get_texture(IMAGE_BOOM));
				blocks_[i * d->get_game()->cols + j] = b;
				add_widget(b);
			}
		}
		auto* t = new timer();
		add_widget(t);
		t->on_tick(1, [d, t](event_args*) {
			if (d->get_game()->get_recording().data.empty()) {
				t->interval = 0;
				return;
			}

			for (auto& point = d->get_game()->get_recording().data.front(); point.timepoint <= d->get_game()->timer.get_elapsed_time(); point = d->get_game()->get_recording().data.front()) {
				if (static_cast<block_type>(point.type) != BOOM)
					d->get_audio_device().play(AUDIO_CLICK);
				d->get_audio_device().play(AUDIO_CLICK);
				d->get_game()->update_hook(point.rows, point.cols, static_cast<block_type>(point.type));
				d->get_game()->get_recording().data.pop_front();
				if (d->get_game()->get_recording().data.empty()) break;
			}
			});
		d->get_game()->update_hook = [=](int x, int y, block_type type)
		{
			blocks_[(x - 1) * d->get_game()->cols + (y - 1)]->update(type);
		};
		d->get_game()->timer.start();
		on_keyboard_keypressed(KEY_ESCAPE, [d, this](auto*)
			{
				d->switch_to(SCENE_MENU);

			});
	}
}
