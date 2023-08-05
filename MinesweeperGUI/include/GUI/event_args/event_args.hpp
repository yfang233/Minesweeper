#pragma once
#ifndef __EVENT_ARGS_H_
#define __EVENT_ARGS_H_

namespace gui
{
	class event_args
	{
	public:
		virtual ~event_args() = default;
		virtual event_args* get_class_type() { return this; }
	};
}

#endif