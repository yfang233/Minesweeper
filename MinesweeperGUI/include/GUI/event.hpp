#pragma once
#ifndef __EVENT_H_
#define __EVENT_H_

#include "GUI/event_args/event_args.hpp"

namespace gui
{
	enum event_type
	{
		event_unknown = 0,
		event_mouse_click,
		event_mouse_hover,
		event_mouse_keydown,
		event_mouse_keyup,
		event_keyboard,
		event_timer_tick,
		event_scene_changed,
		event_count,
	};
	class event
	{
	public:
		explicit event(event_args* args, const event_type type=event_unknown):type(type),args(args){}
		event_type type=event_unknown;
		event_args* args;

	};
}

#endif