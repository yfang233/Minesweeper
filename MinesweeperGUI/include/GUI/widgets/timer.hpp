#pragma once
#ifndef __TIMER_H_
#define __TIMER_H_

#include "GUI/widget.hpp"
#include "GUI/event.hpp"
#include<functional>
#include "GUI/clock.hpp"

namespace gui
{
	class timer : public widget
	{
	public:
		explicit timer(int id = -1) : widget(-1, -1, 0, 0, id) { }
		unsigned int interval = 0;
		void draw() override;
		void on_tick(unsigned int interval, std::function<void(event_args*)> handler);
	private:
		bool waiting_to_tick_ = false;
		util::clock internal_timer_ = util::clock();
		std::function<void(event_args*)> tick_;
	};
}

#endif