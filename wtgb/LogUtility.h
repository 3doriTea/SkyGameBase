#pragma once
#include "pch/pch.h"

#if 1 //_DEBUG

#define LOGF(fmt, ...)\
OutputDebugString(std::format(reinterpret_cast<const char*>(std::u8string{ fmt }.c_str()), __VA_ARGS__).c_str())

#define LOGFLN(fmt, ...)\
OutputDebugString((std::format(fmt, __VA_ARGS__) + "\n").c_str())

#define LOGFW(fmt, ...)\
OutputDebugString(\
	std::format(\
		"[Warning]{}\nfrom:{} - line:{} func:{}",\
		std::format(fmt, __VA_ARGS__),\
		__FILE__,\
		__LINE__,\
		__FUNCTION__).c_str())

#define LOGFWLN(fmt, ...)\
OutputDebugString(\
	(std::format(\
		"[Warning]{}\nfrom:{} - line:{} func:{}",\
		std::format(fmt + "\n", __VA_ARGS__),\
		__FILE__,\
		__LINE__,\
		__FUNCTION__) + "\n").c_str())
#else

#define LOGF
#define LOGFLN
#define LOGFW
#define LOGFWLN

#endif
