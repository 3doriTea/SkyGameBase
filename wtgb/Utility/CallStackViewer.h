#pragma once
#define WIN32_LEAN_AND_MEAN
#include <string>

#pragma comment(lib, "DbgHelp.lib")

namespace wtgb
{
	std::string GetStackTrace(const int _skipFrames);
}
