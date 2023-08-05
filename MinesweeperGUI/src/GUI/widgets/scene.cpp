#include "GUI/widgets/scene.hpp"
#include "GUI/event_args/keyboard_event_args.hpp"
namespace gui
{
	scene::scene(int width, int height, int id) : group(0, 0, width, height, id)
	{
		//parent_ = this;
	}

	void scene::register_event_listener(widget* w, event_type type)
	{
		event_listeners_[type].emplace_back(w);
	}

	void scene::on_keyboard_keypressed(KeyboardKey key, std::function<void(event_args*)> handler)
	{
		register_event(event_keyboard, [this,key](const event& e)
			{
				const auto* args = dynamic_cast<keyboard_event_args*>(e.args);
			if(args->keys[static_cast<int>(key)]&KEYBOARD_KEY_PRESSED)
				return true;
			else
				return false;
			},std::move(handler));
	}
}
