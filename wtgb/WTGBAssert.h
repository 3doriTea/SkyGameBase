#pragma once
#include "pch/pch.h"
#include "Core/Game.h"

#ifdef _DEBUG

#define wassert(expression)\
if (!(expression))\
{\
	std::string description\
	{\
		std::format(\
			"{}\r\n\"{}\"より、{}行目の{}関数内でwassertが起動しました。\r\nキャンセルしない場合、例外スローします。Windowsの最終エラーを取得しますか？(はい/いいえ)",\
			#expression,\
			__FILE__,\
			__LINE__,\
			__FUNCTION__)\
	};\
	std::string title\
	{\
		wtgb::Game::Title()\
	};\
	int result\
	{\
		MessageBox(NULL, description.c_str(), title.c_str(), MB_YESNOCANCEL | MB_ICONSTOP | MB_SYSTEMMODAL)\
	};\
if (result == IDYES)\
{\
	DWORD errorCode{ GetLastError() };\
	MessageBox(NULL, std::format("最終エラーコード:{}", errorCode).c_str(), title.c_str(), MB_OK | MB_ICONSTOP | MB_SYSTEMMODAL);\
	throw "this wassersion error";\
}\
else if (result == IDNO)\
{\
	throw "this wassersion error";\
}\
else\
{\
	wtgb::Game::Exit();\
}\
}

#else

#define wassert(expression)

#endif
