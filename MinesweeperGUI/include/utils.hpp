#pragma once
#ifndef __UTILS_H_
#define __UTILS_H_

//This file is used to implement utilities that are not easy to categorize
namespace util
{
	static bool string_ends_with(std::string_view str, std::string_view substr)
	{
		if (substr.size() > str.size())return false;
		for(auto it1=str.rbegin(),it2=substr.rbegin();it2!=substr.rend();++it1,++it2)
		{
			if (*it1 != *it2)return false;
		}
		return true;
	}
}


#endif