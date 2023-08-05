#pragma once
#ifndef __DIR_H_
#define __DIR_H_
#include<string>
#include<filesystem>
namespace gui::util
{
	class dir
	{
	public:
		static std::string rel_to_abs(const char* rel_path);
		static void set_exec_dir(const char* dir);
		static std::string get_exec_dir();
	private:
		inline static std::filesystem::path exec_dir;
	};
}

#endif