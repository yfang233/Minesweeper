#pragma once
#ifndef __BUTTON_H_
#define __BUTTON_H_

#include "label.hpp"
#include "GUI/widgets/button.hpp"
namespace gui {
	class button : public label {
	public:
		explicit button(int x, int y, int width, int height, int id = -1) : label(x, y, width, height, id) { }
		
	protected:
		void draw() override;

	};
}

#endif