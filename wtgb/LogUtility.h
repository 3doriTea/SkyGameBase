#pragma once
#include "pch/pch.h"

#ifdef _DEBUG

#define LOGF(fmt, ...)\
OutputDebugString(std::format(fmt, __VA_ARGS__).c_str())

#define LOGFW(fmt, ...)\
OutputDebugString(\
	std::format(\
		"[Warning]{}\nfrom:{} - line:{} func:{}",\
		std::format(fmt, __VA_ARGS__),\
		__FILE__,\
		__LINE__,\
		__FUNCTION__).c_str())
#else

#endif
