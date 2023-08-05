#pragma once
#ifndef __GUI_EXCEPTIONS_H_
#define __GUI_EXCEPTIONS_H_
#include<exception>
namespace gui {
	class gui_exception : public std::exception {
	public:
		gui_exception(const char* error_msg) : std::exception(error_msg) {}
	};
}
#endif