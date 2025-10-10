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

wtgb::Result wtgb::GameWindow::Init()
{
	const WNDCLASSEX WNDCLASSEX_DESC
	{
		.cbSize = sizeof(WNDCLASSEX),
		.style = CS_VREDRAW | CS_HREDRAW,
		.lpfnWndProc = WinProc,
		.cbClsExtra = 0,
		.cbWndExtra = 0,
		.hInstance = GetModuleHandle(NULL),
		.hIcon = LoadIcon(nullptr, IDI_APPLICATION),
		.hCursor = LoadCursor(nullptr, IDC_ARROW),
		.lpszMenuName = nullptr,
		.lpszClassName = Game::Title().c_str(),
		.hIconSm = LoadIcon(nullptr, IDI_WINLOGO)
	};

	return Result::Code::Ok;
}

void wtgb::GameWindow::Update()
{
}

void wtgb::GameWindow::End()
{
}

void wtgb::GameWindow::Create(const Config& _config)
{
	WNDCLASSEX windowClass
	{
		.cbSize = sizeof(WNDCLASSEX),
		//.style = CS_  // TODO: ウィンドウクラスEXを実装
		.hInstance = GetModuleHandle(NULL),
	};
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

LRESULT wtgb::GameWindow::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return LRESULT();
}
