#pragma once
#ifndef __GROUP_H_
#define __GROUP_H_

#include<list>

#include "GUI/widget.hpp"
namespace gui
{
	class group : public widget
	{
	public:
		virtual void add_widget(widget* w);
		void add_widget(group* w);
		virtual void remove_widget(widget* w);
		void draw() override;
		explicit group(int x, int y, int width, int height, int id = -1) : widget(x, y, width, height, id) {}
		void event_digest(event& e) override;
		virtual void event_dispatch(event&);
		~group() override;
	protected:
		std::list<widget*> widgets_;
		std::list<widget*> event_listeners_[event_count];
		virtual void register_event_listener(widget* w, event_type type);
		virtual void deregister_event_listener(widget* w, event_type type);
		friend class widget;
	};
}

#endif
