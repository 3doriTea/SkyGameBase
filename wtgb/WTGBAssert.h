#pragma once
#include "pch/pch.h"
#include "Core/Game.h"
#include <cassert>

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
assert(expression)
#endif
//
//#define wassert(expression)\
//if (!(expression))\
//{\
//	DWORD errorCode{ GetLastError() };\
//	std::u8string hint{ u8"特になし" };\
//	switch (errorCode)\
//	{\
//		case 3: hint = u8"ファイルパスを間違えているかも！"; break;\
//		default: break;\
//	}\
//	std::u8string description\
//	{\
//		std::format(\
//			u8"{}\r\n\"{}\"より、{}行目の{}関数内でwassertが起動しました。\r\nキャンセルしない場合、例外スローします。Windowsの最終エラーを取得しますか？(はい/いいえ)\r\nヒント：{}",\
//			#expression,\
//			__FILE__,\
//			__LINE__,\
//			__FUNCTION__,\
//			hint)\
//	};\
//	std::u8string title\
//	{\
//		wtgb::Game::Title()\
//	};\
//	std::string descriptionStd{ description.begin(), description.end() };\
//	std::string titleStd{ titleStd.begin(), titleStd.end() };\
//	int result\
//	{\
//		MessageBox(NULL, descriptionStd.c_str(), title.c_str(), MB_YESNOCANCEL | MB_ICONSTOP | MB_SYSTEMMODAL)\
//	};\
//	/* MessageBoxの表示に失敗したときは、標準のassertを使う */\
//	if (result == 0)\
//	{\
//		assert(false && "wassert: MessageBox failed to display. Falling back to standard assert.");\
//	}\
//	if (result == IDYES)\
//	{\
//		int secResult { MessageBox(NULL, std::format("Last Error Code:{}", errorCode).c_str(), title.c_str(), MB_OK | MB_ICONSTOP | MB_SYSTEMMODAL) };\
//		if (secResult == 0)\
//		{\
//			assert(false && "wassert: secondary MessageBox failed to display.");\
//		}\
//		throw "this wassersion error";\
//	}\
//	else if (result == IDNO)\
//	{\
//		assert(false && "this wassersion");\
//		throw "this wassersion error";\
//	}\
//	else\
//	{\
//		wtgb::Game::Exit();\
//	}\
//}
//
//#else
//
//#define wassert(expression)
//
//#endif
