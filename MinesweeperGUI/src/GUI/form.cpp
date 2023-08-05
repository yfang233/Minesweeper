
#include "GUI/form.hpp"

#include "raylib/raylib.h"
#include<thread>

#include "GUI/gui_exceptions.hpp"
#include "GUI/event_args/keyboard_event_args.hpp"
#include "GUI/event_args/mouse_event_args.hpp"

namespace gui
{
	form::form()
	{
		SetTargetFPS(60);
	}

	form& form::get_instance()
	{
		static form instance;
		return instance;
	}

	form::~form()
	{
		if(initialized_) CloseWindow();
	}

	form& form::set_title(const char* new_title)
	{
		title_ = new_title;
		if (initialized_) SetWindowTitle(title_);
		return *this;
	}

	form& form::set_fps(int fps)
	{
		SetTargetFPS(fps);
		return *this;
	}

	form& form::resize(int width, int height)
	{
		width_ = width;
		height_ = height;
		if (initialized_) SetWindowSize(width, height);
		return *this;
	}

	form& form::resize(Vector2 size)
	{
		width_ = size.x;
		height_ = size.y;
		SetWindowSize(size.x, size.y);
		return *this;
	}

	form& form::set_pos(int x, int y)
	{
		x_ = x;
		y_ = y;
		if (initialized_) SetWindowPosition(x, y);
		return *this;
	}


	const char* form::get_title() const
	{
		return title_;
	}

	bool form::is_initialized() const
	{
		return initialized_;
	}

	void form::show()
	{
		using namespace std::chrono_literals;
		should_close_ = false;
		if (!initialized_) {
#ifdef DEBUG
			SetTraceLogLevel(LOG_DEBUG);
#else
			SetTraceLogLevel(LOG_WARNING);
#endif
			
			InitWindow(width_, height_, title_);
			initialized_ = true;
			for (int i = 0; !IsWindowReady(); i++)
			{
				if (i > 10)throw gui_exception("form initialization out of time limit");
				std::this_thread::sleep_for(50ms);
			}
			SetExitKey(0);
		}

	}

	void form::draw_once()
	{
		if (current_scene == nullptr) throw gui_exception("current scene is null");
		if (!initialized_) show();

		auto* m = new mouse_event_args();
		auto* k = new keyboard_event_args();
		if (!WindowShouldClose() && !should_close_) {
			BeginDrawing();

			DrawFPS(0, 0);

			//mouse events
			m->pos = GetMousePosition();
			m->keyleft = static_cast<key_state>(IsMouseButtonDown(MOUSE_BUTTON_LEFT));
			m->keymiddle = static_cast<key_state>(IsMouseButtonDown(MOUSE_BUTTON_MIDDLE));
			m->keyright = static_cast<key_state>(IsMouseButtonDown(MOUSE_BUTTON_RIGHT));
			m->delta = GetMouseDelta();
			int click_flags = 0;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				click_flags |= mouse_left;
			}
			if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE))
			{
				click_flags |= mouse_middle;
			}
			if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
			{
				click_flags |= mouse_right;
			}
			m->click_flags = click_flags;
			if (click_flags != 0)
				event_queue.push(event(m, event_mouse_click));
			else
				event_queue.push(event(m, event_mouse_hover));
			//TODO: support more events

			//keyboard events
			for (int i = 0; i < 512; i++)
			{
				const int tmp = (IsKeyReleased(i) << 2) + (IsKeyPressed(i) << 1) + (IsKeyDown(i));
				k->keys[i] = tmp;
			}
			event_queue.push(event(k, event_keyboard));

			while (!event_queue.empty())
			{
				event i = event_queue.front();
				current_scene->event_dispatch(i);
				event_queue.pop();
			}
			ClearBackground(current_scene->background_color);
			current_scene->draw_handler();

			EndDrawing();
		}
		delete m;
		delete k;
	}

	void form::close()
	{
		if (initialized_) {
			should_close_ = true;
			initialized_ = false;
		}
	}

	void form::draw_until_window_closed()
	{

		if (current_scene == nullptr) throw gui_exception("current scene is null");
		if (!initialized_) show();

		auto* m = new mouse_event_args();
		auto* k = new keyboard_event_args();
		while (!WindowShouldClose()&&!should_close_) {
			BeginDrawing();
#ifdef DEBUG
			DrawFPS(0, 0);
#endif
			//mouse events
			m->pos = GetMousePosition();
			m->keyleft = static_cast<key_state>(IsMouseButtonDown(MOUSE_BUTTON_LEFT));
			m->keymiddle = static_cast<key_state>(IsMouseButtonDown(MOUSE_BUTTON_MIDDLE));
			m->keyright = static_cast<key_state>(IsMouseButtonDown(MOUSE_BUTTON_RIGHT));
			m->delta=GetMouseDelta();
			int click_flags = 0;
			if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				click_flags |= mouse_left;
			}
			if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE))
			{
				click_flags |= mouse_middle;
			}
			if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
			{
				click_flags |= mouse_right;
			}
			m->click_flags = click_flags;
			if (click_flags != 0)
				event_queue.push(event(m, event_mouse_click));
			else
				event_queue.push(event(m, event_mouse_hover));
			//TODO: support more events

			//keyboard events
			for(int i=0;i<512;i++)
			{
				const int tmp = (IsKeyReleased(i) << 2) + (IsKeyPressed(i) << 1) + (IsKeyDown(i));
				k->keys[i] = tmp;
			}
			event_queue.push(event(k, event_keyboard)); 

			while(!event_queue.empty())
			{
				event i = event_queue.front();
				current_scene->event_digest(i);
				event_queue.pop();
			}
			ClearBackground(current_scene->background_color);
			current_scene->draw_handler();

			EndDrawing();
		}
		initialized_ = false;
		CloseWindow();
		delete m;
		delete k;
	}

	
	

}
