#pragma once
#ifndef __EXCEPTIONS_H_
#define __EXCEPTIONS_H_

#include<exception>
namespace minesweeper
{
	class file_corrupted_exception : public std::exception {};
	class file_exception : public std::exception
	{
	public:
		file_exception(const char* errormsg) : std::exception(errormsg) {}
	};
	class game_exception : public std::exception
	{
	public:
		game_exception(const char* errormsg) : std::exception(errormsg) {}
	};
}

#endif