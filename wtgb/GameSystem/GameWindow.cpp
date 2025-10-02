#include "pch\pch.h"
#include "GameWindow.h"
#include "Core/Game.h"

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
		.lpfnWndProc = [this](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) -> LRESULT
		{

		},
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
