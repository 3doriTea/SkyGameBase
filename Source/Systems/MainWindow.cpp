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
	GameWindowHandle hGameWindow
	{
		_viewer.Get<GameWindow>().Create(
		{
			.title = Game::Title(),
			.classStyle = CS_VREDRAW | CS_HREDRAW,
			.icon = LoadIcon(nullptr, IDI_APPLICATION),
			.iconSmile = LoadIcon(nullptr, IDI_WINLOGO),
			.cursor = LoadCursor(nullptr, IDC_ARROW),
			.clientStyle = WS_OVERLAPPEDWINDOW,
			.clientStyleEx = WS_EX_OVERLAPPEDWINDOW,
			.hasMenu = FALSE,
			// TODO: スクリーンサイズをinitファイルから読み込む
			.windowScreenSize = { 1600, 900 },
			.initPosition = { 50, 50 },
			.hWndParent = nullptr,
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
