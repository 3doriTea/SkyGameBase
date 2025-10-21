#pragma once
#include "pch/pch.h"
#include "Core/Game.h"

/*
* NOTE: wassertの式内でRelease時も必要な関数を入れないでください。
*     : wassertはReleaseビルド時に式ごと無視されるため、適切なアサーション処理をしてください。
*     : 適切なアサーション処理は、戻り値を一度変数に格納し、その変数をwassertの式に埋め込む形になります。
* Bad Code:
*   wassert(RegisterClassEx(&WNDCLASSEX_DESC) != 0
*     && "ウィンドウクラス登録に失敗");
* Good Code:
*   ATOM atom{ RegisterClassEx(&WNDCLASSEX_DESC) };
*   wassert(atom != 0 && "ウィンドウクラス登録に失敗");
*/

#ifdef _DEBUG

#define wassert(expression)\
if (!(expression))\
{\
	DWORD errorCode{ GetLastError() };\
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
