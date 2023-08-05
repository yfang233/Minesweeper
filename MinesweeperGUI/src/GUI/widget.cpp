#include <utility>

#include "GUI/widget.hpp"
#include "GUI/gui_exceptions.hpp"
#include "GUI/event_args/mouse_event_args.hpp"
#include "GUI/widgets/group.hpp"

namespace gui
{
	widget& widget::resize(int width,int height){
		this->width_ = width;
		this->height_ = height;
		return *this;
	}

	void widget::remove_from_parent()
	{
		if (parent_ == nullptr) throw gui_exception("parent cannot be nullptr");
		parent_->remove_widget(this);
		parent_ = nullptr;
	}

	void widget::register_event(event_type type, std::function<bool(event&)> cond, std::function<void(event_args*)> handler)
	{
		listeners_[type] = { true, std::move(cond),std::move(handler) };
		if (parent_!=nullptr) 
			parent_->register_event_listener(this, type);

	}

	void widget::deregister_event(event_type type)
	{
		if (parent_==nullptr) 
			throw gui_exception("you have to attach a widget to a group(scene) before registering event");
		parent_->deregister_event_listener(this, type);
		listeners_[type].listening=false;
	}

	widget::~widget()
	{
		//deregister all event listeners of this widget
		if (parent_ != nullptr)
		{
			remove_from_parent();
		}
	}

	void widget::on_click(std::function<void(event_args*)> handler)
	{
		register_event(event_mouse_click, [this](const event& e)
			{
				const auto* args = dynamic_cast<mouse_event_args*>(e.args);
				const auto x_ = get_pos().x;
				const auto y_ = get_pos().y;
				const auto width_ = get_size().x;
				const auto height_ = get_size().y;
				if (args->pos.x >= x_ && args->pos.x <= x_ + width_ && args->pos.y >= y_ && args->pos.y <= y_ + height_)
				{
					return true;
				}
				return false;
			}, std::move(handler));
	}

	Vector2 widget::get_pos() const
	{
		return Vector2{static_cast<float>(x_),static_cast<float>(y_)};
	}

	Vector2 widget::get_size() const
	{
		return Vector2{ static_cast<float>(width_),static_cast<float>(height_) };
	}

	widget& widget::set_pos(int x, int y)
	{
		x_ = x;
		y_ = y;
		return *this;
	}

	void widget::event_digest(event& e)
	{
		if (enabled && listeners_[e.type].listening && listeners_[e.type].cond(e))
		{
			listeners_[e.type].handler(e.args);
		}
	}

	void widget::draw_handler()
	{
		if (enabled) draw();
	}
}
