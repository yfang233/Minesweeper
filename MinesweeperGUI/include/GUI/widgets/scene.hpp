#pragma once
#ifndef __SCENE_H_
#define __SCENE_H_

#include "GUI/widgets/group.hpp"
namespace gui
{
	class scene: public group
	{
	public:
		explicit scene(int width, int height, int id = -1);
		~scene() override = default;
		void register_event_listener(widget* w, event_type type) override;
		void on_keyboard_keypressed(KeyboardKey key, std::function<void(event_args*)> handler);
		Color background_color = WHITE;
	};
}

#endif