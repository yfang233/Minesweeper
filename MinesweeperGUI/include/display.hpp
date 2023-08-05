#pragma once
#ifndef __DISPLAY_H_
#define __DISPLAY_H_

#include "gui.hpp"
#include<vector>
#include "raylib/raylib.h"
#include "game.hpp"
#include "audio.hpp"

namespace minesweeper
{
	constexpr int block_length = 40;
	constexpr int block_spacing = 5;

	enum image_resources
	{
		IMAGE_FLAG=0,
		IMAGE_BOOM,
		IMAGE_MINE,
		IMAGE_COUNT
	};

	enum game_scenes
	{
		SCENE_MENU,
		SCENE_LEVEL_SELECT,
		SCENE_GAMING,
		SCENE_PAUSED,
		SCENE_VICTORY,
		SCENE_REPLAY,
		SCENE_DEFEAT,
		SCENE_SHOWLIST,
		SCENE_RANKLIST,
		SCENE_COUNT
		
	};

	class display
	{
	public:
		display();
		~display();
		display(display&&) = default;
		void display_scene(game_scenes s, void* args = nullptr);
		void switch_to(game_scenes s);
		void release_scene(game_scenes s);
		game* get_game() const;
		void set_game(game* g);
		audio& get_audio_device() const;
		Texture& get_texture(image_resources res);
	private:
		//Unexpected display object copy can cause texture UAF
		display(const display&) = default;
		std::vector<gui::scene*> scenes_ = std::vector<gui::scene*>(SCENE_COUNT);
		std::unordered_map<int, std::function<gui::scene*(void*)>> scene_initializers_;
		audio& audio_ = audio::get_instance();
		game* game_ = nullptr;
		std::vector<Texture> texture_data_ = std::vector<Texture>(IMAGE_COUNT);
	};
}

#endif