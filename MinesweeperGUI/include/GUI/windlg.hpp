#pragma once
#ifndef __WINDLG_H_
#define __WINDLG_H_
#include<string>
#include<vector>

namespace gui
{
	struct filename_filter
	{
		const char* description;
		const char* pattern;
	};

	class windlg
	{
	public:
		static void ShowMessageBox(const char* title, const char* text);
		static std::string ShowOpenFileDialog(const std::vector<filename_filter>&);
		static std::string ShowSaveFileDialog(const std::vector<filename_filter>&);
	};

	
}

#endif