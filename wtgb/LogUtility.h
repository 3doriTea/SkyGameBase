#pragma once
#include "pch/pch.h"

#ifdef _DEBUG

#define LOGF(fmt, ...)\
do\
{\
	OutputDebugString(std::format(reinterpret_cast<const char*>(std::u8string{ fmt }.c_str()), __VA_ARGS__).c_str());\
} while (false)

#define LOGFLN(fmt, ...)\
do\
{\
OutputDebugString((std::format(fmt, __VA_ARGS__) + "\n").c_str());\
} while (false)

#define LOGFW(fmt, ...)\
do\
{\
OutputDebugString(\
	std::format(\
		"[Warning]{}\nfrom:{} - line:{} func:{}",\
		std::format(fmt, __VA_ARGS__),\
		__FILE__,\
		__LINE__,\
		__FUNCTION__).c_str());\
} while (false)

#define LOGFWLN(fmt, ...)\
do\
{\
OutputDebugString(\
	(std::format(\
		"[Warning]{}\nfrom:{} - line:{} func:{}",\
		std::format(fmt + "\n", __VA_ARGS__),\
		__FILE__,\
		__LINE__,\
		__FUNCTION__) + "\n").c_str());\
} while (false)
#else

#define LOGF
#define LOGFLN
#define LOGFW
#define LOGFWLN

#endif
