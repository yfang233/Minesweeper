#pragma once
#ifndef __WIDGET_H_
#define __WIDGET_H_

#include "GUI/event.hpp"
#include "raylib/raylib.h"
#include<functional>

namespace gui
{
	class group;
	class event;
	struct event_listener
	{
		bool listening = false;
		std::function<bool(event&)> cond;
		std::function<void(event_args*)> handler;
	};
	class widget
	{
	public:
		widget(int x, int y, int width, int height, int id=-1) : id_(id),x_(x),y_(y),width_(width),height_(height){}
		virtual ~widget();
		Vector2 get_pos() const;
		Vector2 get_size() const;
		virtual widget& set_pos(int x, int y);
		virtual void event_digest(event& e);
		virtual void draw_handler();
		virtual widget& resize(int width, int height);
		void remove_from_parent(); //After removing from parent group, event listeners will be cleared, and you have to register events again after attaching to a new group
		virtual void register_event(event_type type, std::function<bool(event&)> cond, std::function<void(event_args*)> handler);
		virtual void deregister_event(event_type type);
		virtual void on_click(std::function<void(event_args*)> handler);
		int id_;
		bool enabled = true;
	protected:
		int x_;
		int y_;
		int width_;
		int height_;
		virtual void draw() = 0;
		event_listener listeners_[event_count];
		group* parent_ = nullptr;
		friend class group;
	};
}

#endif