#include "GUI/widgets/timer.hpp"

#include "GUI/form.hpp"

namespace gui
{
	void timer::draw()
	{
		if (interval == 0) return;
		if (internal_timer_.get_elapsed_time()>=interval)
		{
			event_queue.push(event(nullptr, event_timer_tick));
			waiting_to_tick_ = true;
			internal_timer_.clear();
		}
	}

	void timer::on_tick(unsigned interval, std::function<void(event_args*)> handler)
	{
		timer::interval = interval;
		tick_ = std::move(handler);
		internal_timer_.reset();
		internal_timer_.start();
		register_event(event_timer_tick, [this](event _)
			{
				if (this->waiting_to_tick_)
				{
					this->waiting_to_tick_ = false;
					return true;
				}
				else
				{
					return false;
				}
			}, tick_);
	}

}
