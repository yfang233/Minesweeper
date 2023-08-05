#include "GUI/widgets/group.hpp"
#include<algorithm>
using namespace std;
namespace gui
{
	void group::add_widget(widget* w)
	{
		widgets_.emplace_back(w);
		w->parent_ = this;
		for(auto i = 0;i<event_count;i++)
		{
			if (w->listeners_[i].listening) {
				if (parent_ != nullptr && event_listeners_[i].empty()) parent_->register_event_listener(this, static_cast<event_type>(i));
				event_listeners_[i].emplace_back(w);
			}
		}
	}

	void group::add_widget(group* w)
	{
		widgets_.emplace_back(w);
		w->parent_ = this;
		for (auto i = 0; i < event_count; i++)
		{
			if (w->listeners_[i].listening || !w->event_listeners_[i].empty()) {
				if (parent_ != nullptr && event_listeners_[i].empty()) parent_->register_event_listener(this, static_cast<event_type>(i));
				event_listeners_[i].emplace_back(w);
			}
		}
	}

	void group::remove_widget(widget* w)
	{
		for(int i=0;i<event_count;i++)
		{
			deregister_event_listener(w, static_cast<event_type>(i));
		}
		widgets_.erase(remove_if(
			widgets_.begin(),
			widgets_.end(),
			[w](const widget* widget)
			{
				return w == widget;
			}
		), widgets_.end());
	}

	void group::draw()
	{
		for (const auto obj : widgets_)
		{
			obj->draw_handler();
		}
	}

	void group::event_digest(event& e)
	{
		widget::event_digest(e);
		event_dispatch(e);
	}

	void group::event_dispatch(event& e)
	{
		for(const auto i : event_listeners_[e.type])
		{
			i->event_digest(e);
		}
	}

	void group::register_event_listener(widget* w, const event_type type)
	{
		if (parent_ != nullptr && event_listeners_[type].empty()) parent_->register_event_listener(this, type);
		event_listeners_[type].emplace_back(w);
	}

	void group::deregister_event_listener(widget* w, event_type type)
	{
		if(!event_listeners_[type].empty())
		{
			event_listeners_[type].erase(remove_if(
				event_listeners_[type].begin(),
				event_listeners_[type].end(),
				[w](widget*& i)
				{
					return i == w;
				}), event_listeners_[type].end());
			if (parent_ != nullptr && event_listeners_[type].empty())
				parent_->deregister_event_listener(this, type);
		}

	}

	group::~group()
	{
		for(const auto widget : widgets_)
		{
			//As the destructor of widget will remove it from parent group, widgets_ will be modified here and cause segfault. So, we need to set widget->parent_ to nullptr.
			widget->parent_ = nullptr;
			delete widget;
		}
	}
}
