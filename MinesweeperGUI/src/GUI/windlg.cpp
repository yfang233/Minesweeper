

#include "Windows.h"
#include "WinUser.h"
#include "commdlg.h"
#include "GUI/windlg.hpp"

using namespace std;

namespace gui
{
	void windlg::ShowMessageBox(const char* title, const char* text)
	{
		MessageBoxA(NULL, text, title, MB_OK);
	}

	OPENFILENAME* init_ofn(const std::vector<filename_filter>& filters)
	{
		char* filter_str = new char[512];
		memset(filter_str, 0, 512);
		if (filters.empty())
		{
			constexpr char default_filter[] = "All Files\0*.*\0";
			memcpy(filter_str, default_filter, sizeof(default_filter));
		}

		char* filename_buf = new char[512];
		filename_buf[0] = '\0';
		string strFilter = string();
		for (const auto i : filters)
		{
			strFilter += i.description;
			strFilter.push_back('\0');
			strFilter += i.pattern;
			strFilter.push_back('\0');
		}
		if (strFilter.size() > 510) throw exception("filter string too long");
		//As we've already memset filter_str to 0, it is assured to end with multiple '\0'
		memcpy(filter_str, strFilter.c_str(), strFilter.size());
		return new OPENFILENAME{
			sizeof(OPENFILENAME),
			NULL,
			NULL,
			filter_str,
			NULL,
			NULL,
			1,
			filename_buf,
			512,
			NULL,
			0,
			NULL,
			NULL,
			OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
			NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
		};
	}

	void fini_ofn(const OPENFILENAME* ofn)
	{
		delete[] ofn->lpstrFile;
		delete[] ofn->lpstrFilter;
		delete ofn;
	}

	std::string windlg::ShowOpenFileDialog(const std::vector<filename_filter>& filters)
	{
		if (auto* ofn = init_ofn(filters); GetOpenFileName(ofn))
		{
			std::string result(ofn->lpstrFile);
			fini_ofn(ofn);
			return result;
		}
		else
		{
			fini_ofn(ofn);
			return {};
		}
	}

	std::string windlg::ShowSaveFileDialog(const std::vector<filename_filter>& filters)
	{
		auto* ofn = init_ofn(filters);
		if (GetSaveFileName(ofn))
		{
			std::string result(ofn->lpstrFile);
			fini_ofn(ofn);
			return result;
		}
		else
		{
			fini_ofn(ofn);
			return {};
		}
	}
}

