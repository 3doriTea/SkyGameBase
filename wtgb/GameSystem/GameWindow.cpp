#include "pch\pch.h"
#include "GameWindow.h"
#include "Core/Game.h"
#include "WTGBAssert.h"

#include "GameSystem/Input.h"
#include "GameSystem/Cursor.h"

using namespace wtgb;

wtgb::GameWindow::GameWindow() :
	peekedMessage_{}
{
}

wtgb::GameWindow::~GameWindow()
{
}

wtgb::Result wtgb::GameWindow::Init(const ViewerInit& _viewer)
{
	return Result::Code::Ok;
}

void wtgb::GameWindow::Update(const ViewerUpdate& _system)
{
	// MEMO: すべてのウィンドウからのメッセージを受信するため第２引数は nullptr
	if (PeekMessage(&peekedMessage_, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&peekedMessage_);
		DispatchMessage(&peekedMessage_);
	}

	// マウス座標を更新する
	_system.Get<Input>().GetMouseUpdater().SetMousePosition(mousePosition_);
	_system.Get<Cursor>().GetUpdater().UpdatePosition(mousePosition_);
}

void wtgb::GameWindow::End()
{
	// 全ウィンドウを閉じる && 解放
	windowHandles_.Release([](CreatedWindowData& _data)
	{
		CloseWindow(_data.hWnd);
		DestroyWindow(_data.hWnd);
	});

	winProcCallbacks_.clear();
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

	GameWindowHandle hGameWindow{ windowHandles_.Emplace(_config, hWnd) };

	ShowWindow(hWnd, SW_SHOWDEFAULT);  // ウィンドウを表示

	return hGameWindow;
}

HWND wtgb::GameWindow::GetMainWindowHandle()
{
	wassert(!windowHandles_.IsEmpty() && "ウィンドウハンドルが1つも登録されていない");
	return windowHandles_.begin()->second.hWnd;
}

wtgb::Vector2Int wtgb::GameWindow::GetMainWindowSize()
{
	return GetMainWindowData().windowScreenSize;
}

wtgb::GameWindow::RefreshRate wtgb::GameWindow::GetMainWindowRefreshRate()
{
	return GetMainWindowData().refreshRateSec;
}

BOOL wtgb::GameWindow::GetMainWindowIsWindowed()
{
	return GetMainWindowData().windowed;
}

BOOL wtgb::GameWindow::IsActiveMainWindow()
{
	return GetMainWindowHandle() == GetForegroundWindow();
}

void wtgb::GameWindow::AddWinProcListener(const std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>& _callback)
{
	winProcCallbacks_.push_back(_callback);
}

const wtgb::GameWindow::CreateWindowConfig& wtgb::GameWindow::GetMainWindowData()
{
	wassert(!windowHandles_.IsEmpty() && "ウィンドウハンドルが1つも登録されていない");
	return windowHandles_.begin()->second.config;
}

LRESULT wtgb::GameWindow::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	isDefaultControled_ = true;

	// システムが受け取りたい処理を先にする
	for (auto& callback : winProcCallbacks_)
	{
		if (callback(hWnd, message, wParam, lParam))
		{
			isDefaultControled_ = false;
			// 受け取れたなら回帰
			return true;
		}
	}

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
		mousePosition_.x = LOWORD(lParam);
		mousePosition_.y = HIWORD(lParam);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

wtgb::Vector2Int wtgb::GameWindow::mousePosition_{};
std::list<std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>> wtgb::GameWindow::winProcCallbacks_{};
bool wtgb::GameWindow::isDefaultControled_{};
