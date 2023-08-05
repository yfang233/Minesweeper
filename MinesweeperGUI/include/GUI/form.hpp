#pragma once
#ifndef __FORM_H_
#define __FORM_H_

#include <queue>

#include "GUI/widgets/scene.hpp"

namespace gui{
	inline std::queue<event> event_queue;
    class form final
	{
	public:
		static form& get_instance();
		scene* current_scene = nullptr;
		const char* get_title() const;
		bool is_initialized() const;
		form& set_title(const char* new_title);
		form& set_fps(int fps);
		form& resize(int width, int height);
		form& resize(Vector2 size);
		form& set_pos(int x, int y);
		void draw_until_window_closed();
		void show();

		void draw_once(); // for debugging purpose

		void close();

	private:
		form();
		~form();
		form(const form&) = default;
		form& operator=(const form&) = default;
		const char* title_ = "MinesweeperGUI";
		bool initialized_ = false;
		bool should_close_ = false;
		int x_ = 0, y_ = 0, width_ = 1280, height_ = 720;
	};
}

#endif