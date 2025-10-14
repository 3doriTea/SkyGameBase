#include "pch\pch.h"
#include "GameWindow.h"
#include "Core/Game.h"
#include "WTGBAssert.h"

//#include "GameSystem/Input.h"

wtgb::GameWindow::GameWindow()
{
}

wtgb::GameWindow::~GameWindow()
{
}

wtgb::Result wtgb::GameWindow::Init(const Viewer& _viewer)
{
	return Result::Code::Ok;
}

void wtgb::GameWindow::Update()
{
	// MEMO: すべてのウィンドウからのメッセージを受信するため第２引数は nullptr
	if (PeekMessage(&peekedMessage_, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&peekedMessage_);
		DispatchMessage(&peekedMessage_);
	}
}

void wtgb::GameWindow::End()
{
}

wtgb::GameWindowHandle wtgb::GameWindow::Create(const CreateWindowConfig& _config)
{
	HINSTANCE hInstance{ GetModuleHandle(NULL) };

	const WNDCLASSEX WNDCLASSEX_DESC
	{
		.cbSize        = sizeof(WNDCLASSEX),
		.style         = _config.classStyle,
		.lpfnWndProc   = WinProc,
		.cbClsExtra    = 0,
		.cbWndExtra    = 0,
		.hInstance     = hInstance,
		.hIcon         = _config.icon,
		.hCursor       = _config.cursor,
		.lpszMenuName  = nullptr,
		.lpszClassName = _config.title.data(),
		.hIconSm       = _config.iconSmile,
	};

	ATOM atom{ RegisterClassEx(&WNDCLASSEX_DESC) };
	wassert(atom != 0 && "ウィンドウクラス登録に失敗");

	RECT windowRect{ 0, 0, _config.windowScreenSize.x, _config.windowScreenSize.y };
	BOOL succeed{ AdjustWindowRectEx(&windowRect, _config.clientStyle, _config.hasMenu, _config.clientStyleEx) };
	wassert(succeed && "クライアント領域を考慮したウィンドウサイズ計算に失敗");

	// 計算されたウィンドウのサイズ 横幅
	int windowWidth{ windowRect.right - windowRect.left };
	// 計算されたウィンドウのサイズ 高さ
	int windowHeight{ windowRect.bottom - windowRect.top };

	HWND hWnd = CreateWindowEx(
		_config.clientStyleEx,
		_config.title.data(),
		_config.title.data(),
		_config.clientStyle,
		_config.initPosition.x,
		_config.initPosition.y,
		windowWidth,
		windowHeight,
		_config.hWndParent,
		nullptr,
		hInstance,
		nullptr);

	wassert(hWnd != nullptr && "ウィンドウの作成に失敗");
	wassert(IsWindow(hWnd) && "ウィンドウではないハンドルが作られている");

	GameWindowHandle hGameWindow{ windowHandles_.Emplace(hWnd) };

	ShowWindow(hWnd, SW_SHOWDEFAULT);  // ウィンドウを表示

	return hGameWindow;
}

HWND wtgb::GameWindow::GetMainWindowHandle()
{
	wassert(!windowHandles_.IsEmpty() && "ウィンドウハンドルが登録されていない");
	return windowHandles_.begin()->second;
}

LRESULT wtgb::GameWindow::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:  // メニューとかのコマンド
	{
		int wmId{ LOWORD(wParam) };

		// 選択されたId
		switch (wmId)
		{
		case 0:
			break;
		default:
			LOGFW("未指定のコマンドを受け取った:{}\n", wmId);
			break;
		}
		break;
	}
	case WM_DESTROY:  // ウィンドウを閉じる処理
		Game::Exit();
		break;
	case WM_MOUSEMOVE:
		// TODO: マウス移動を検知する
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
