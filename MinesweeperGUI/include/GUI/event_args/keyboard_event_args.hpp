#pragma once
#ifndef __KEYBOARD_EVENT_ARGS_H_
#define __KEYBOARD_EVENT_ARGS_H_

#include "GUI/event_args/event_args.hpp"

#include<vector>
namespace gui
{
	enum keyboard_key_state
	{
		KEYBOARD_KEY_DOWN=0b1,
		KEYBOARD_KEY_PRESSED=0b10,
		KEYBOARD_KEY_RELEASED=0b100
	};
	class keyboard_event_args : public event_args
	{
	public:
		std::vector<char> keys = std::vector<char>(512);
		event_args* get_class_type() override { return this; }
	};
}

#endif