#include "pch\pch.h"

#include "Core/Game.h"

#include "MainWindow.h"
#include "GameSystem/GameWindow.h"

using namespace wtgb;

MainWindow::MainWindow()
{
}

MainWindow::~MainWindow()
{
}

wtgb::Result MainWindow::Init(const ViewerInit& _viewer)
{
	const char* SETTING_FILE_NAME{ "./setting.ini" };

	const uint32_t WINDOW_WIDTH       { GetPrivateProfileInt("Window", "Width", 1600, SETTING_FILE_NAME) };
	const uint32_t WINDOW_HEIGHT      { GetPrivateProfileInt("Window", "Height", 900, SETTING_FILE_NAME) };
	const uint32_t WINDOW_INIT_POS_X  { GetPrivateProfileInt("Window", "InitPosX", 50, SETTING_FILE_NAME) };
	const uint32_t WINDOW_INIT_POS_Y  { GetPrivateProfileInt("Window", "InitPosY", 50, SETTING_FILE_NAME) };
	const uint32_t WINDOW_REFRESH_RATE{ GetPrivateProfileInt("Window", "RefreshRate", 60, SETTING_FILE_NAME) };

	GameWindowHandle hGameWindow
	{
		_viewer.Get<GameWindow>().Create(GameWindow::CreateWindowConfig
		{
			.title = Game::Title(),
			.classStyle = CS_VREDRAW | CS_HREDRAW,
			.icon = LoadIcon(nullptr, IDI_APPLICATION),
			.iconSmile = LoadIcon(nullptr, IDI_WINLOGO),
			.cursor = LoadCursor(nullptr, IDC_ARROW),
			.clientStyle = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
			.clientStyleEx = WS_EX_OVERLAPPEDWINDOW,
			.hasMenu = FALSE,
			.windowScreenSize = { static_cast<int32_t>(WINDOW_WIDTH), static_cast<int32_t>(WINDOW_HEIGHT) },
			.initPosition = { static_cast<int32_t>(WINDOW_INIT_POS_X), static_cast<int32_t>(WINDOW_INIT_POS_Y) },
			.hWndParent = nullptr,
			.refreshRateSec = WINDOW_REFRESH_RATE,
		})
	};

	return Result::Code::Ok;
}

void MainWindow::Update(const ViewerUpdate& _system)
{
}

void MainWindow::End()
{
}
