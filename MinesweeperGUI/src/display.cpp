#include "display.hpp"
#include <unordered_map>

#include "exceptions.hpp"
#include "game.hpp"
#include "scenes/menu.hpp"
#include "scenes/gaming.hpp"
#include "scenes/level_select.hpp"
#include "scenes/paused.hpp"
#include "GUI/dir.hpp"
#include "scenes/victory.hpp"
#include "scenes/defeat.hpp"
#include "scenes/replay.hpp"
#include "scenes/showlist.hpp"
#include "scenes/ranklist_display.hpp"

using namespace gui;
namespace minesweeper
{
	struct image_info
	{
		image_resources type;
		const char* filename;
		int width;
		int height;
	};

	//The ratio of icon_width and block_length
	constexpr float icon_ratio = 0.7f;

	constexpr image_info images[] = {
		//TODO: images' size not decided yet!
		//warning: MAKE SURE ARRAY INDEX MATCHES IMAGE TYPE
		{IMAGE_FLAG,"assets/images/flag.png",static_cast<int>(block_length * icon_ratio),static_cast<int>(block_length * icon_ratio)},
		{IMAGE_BOOM,"assets/images/boom.png",static_cast<int>(block_length * icon_ratio),static_cast<int>(block_length * icon_ratio)},
		{IMAGE_MINE,"assets/images/mine.png",static_cast<int>(block_length * icon_ratio),static_cast<int>(block_length * icon_ratio)},
	};

	

	display::display()
	{
		form::get_instance().show();
		const auto icon = LoadImage(gui::util::dir::rel_to_abs("assets/images/icon.png").c_str());
		SetWindowIcon(icon);
		UnloadImage(icon);
		for (int i = 0; i < IMAGE_COUNT; i++)
		{
			auto image_data = LoadImage(gui::util::dir::rel_to_abs(images[i].filename).c_str());
			if (image_data.data != nullptr)
			{
				ImageResize(&image_data, images[i].width, images[i].height);

				switch (i)
				{
				case IMAGE_FLAG:
				case IMAGE_BOOM:
				case IMAGE_MINE:
					//for these three images, it would be inconvenient to set the position of imagebox, so we choose to have a same-size image as block_length, but putting the icon in the middle.
					ImageResizeCanvas(&image_data, block_length, block_length, block_length * ((1-icon_ratio)/2.0), block_length * ((1 - icon_ratio) / 2.0), BLANK);
				}

				texture_data_[i] = LoadTextureFromImage(image_data);
				UnloadImage(image_data);
			}
		}

		scene_initializers_ = {
			//TODO: set scenes
			{SCENE_MENU,[this](auto*)
			{
				return new menu(this);
			}},
			{SCENE_LEVEL_SELECT,[this](auto*)
			{
				return new level_select(this);
			}},
			{SCENE_PAUSED,[this](auto*)
			{
				return new paused(this);
			}},
			{SCENE_GAMING,[this](auto*)
			{
				return new gaming(this);
			}},
			{SCENE_VICTORY,[this](void* p)
			{
				const int rank = *(static_cast<int*>(p));
				return new victory(this,rank);
			}},
			{SCENE_REPLAY,[this](auto*)
			{
				return new replay(this);
			}},
			{SCENE_DEFEAT,[this](auto*)
			{
				return new defeat(this);
			}},
			{SCENE_SHOWLIST,[this](auto*)
			{
				return new showlist(this);
			}},
			{SCENE_RANKLIST,[this](void* p)
			{
				return new ranklist_display(this,*(static_cast<ranklist_args*>(p)));
			}}
		};

	}

	display::~display()
	{
		for (int i = 0; i < IMAGE_COUNT; i++)
		{
			if(texture_data_[i].id!=0) UnloadTexture(texture_data_[i]);
		}
		for (const auto* i : scenes_)
		{
			delete i;
		}
		delete game_;
	}

	void display::switch_to(game_scenes s)
	{
		if (scenes_[s] == nullptr)
			scenes_[s] = scene_initializers_.find(s)->second(nullptr);
		form::get_instance().current_scene = scenes_[s];
		form::get_instance().resize(scenes_[s]->get_size());
	}

	void display::display_scene(game_scenes s, void* args)
	{
		delete scenes_[s];
		scenes_[s] = scene_initializers_.find(s)->second(args);
		form::get_instance().current_scene = scenes_[s];
		form::get_instance().resize(scenes_[s]->get_size());
	}

	void display::release_scene(game_scenes s)
	{
		if (scenes_[s] != nullptr)
			throw game_exception("releasing a null scene*");
		else
		{
			delete scenes_[s];
			scenes_[s] = nullptr;
		}
			
	}

	game* display::get_game() const
	{
		return game_;
	}

	void display::set_game(game* g)
	{
		delete game_;
		game_ = g;
	}

	audio& display::get_audio_device() const
	{
		return audio_;
	}

	Texture& display::get_texture(image_resources res)
	{
		return texture_data_[res];
	}
}
