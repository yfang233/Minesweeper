#include "GUI/dir.hpp"
#include<filesystem>
using namespace std::filesystem;
namespace gui::util
{
	std::string dir::rel_to_abs(const char* rel_path)
	{
		if (exec_dir.empty()) throw std::exception("exec_dir is empty");
		path p(exec_dir);
		p += path::preferred_separator;
		p += rel_path;
		return p.string();
	}

	void dir::set_exec_dir(const char* dir)
	{
		const path p(dir);
		if(p.has_filename())
		{
			exec_dir = p.parent_path();
		} else if(is_directory(p))
		{
			exec_dir = canonical(p);
		} else
		{
			throw std::exception("invalid path");
		}
	}

	std::string dir::get_exec_dir()
	{
		return exec_dir.string();
	}
}
