#pragma once
#ifndef __MOUSE_EVENT_ARGS_H_
#define __MOUSE_EVENT_ARGS_H_

#include "GUI/event_args/event_args.hpp"
namespace gui
{
	enum key_state
	{
		state_keydown = 1,
		state_keyup = 0
	};
	enum mouse_key_flags
	{
		mouse_left = 1,
		mouse_middle=0b10,
		mouse_right=0b100
	};
	class mouse_event_args : public event_args
	{
	public:
		mouse_event_args()=default;
		mouse_event_args(Vector2 pos, key_state left, key_state middle, key_state right, Vector2 delta) : pos(pos), keyleft(left), keymiddle(middle), keyright(right), delta(delta) {}
		Vector2 pos;
		key_state keyleft;
		key_state keymiddle;
		key_state keyright;
		int click_flags=0;
		Vector2 delta;
		event_args* get_class_type() override { return this; }
	};
}

#endif