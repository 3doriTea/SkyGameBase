#include "pch\pch.h"
#include "SampleGame.h"

#include "GameSystem/GameTime.h"
#include "GameSystem/Debug.h"
#include "GameSystem/Direct3D.h"
#include "GameSystem/GameWindow.h"
#include "GameSystem/Input.h"

#include "MainWindow.h"

using namespace wtgb;

void SampleGame::StartRegister(
	const GameSystemCollection::GameSystemAdder& _gameSystemRegister)
{
	// TODO: 登録順番が厳しいところが難儀 ユーザからするとここは不便
	_gameSystemRegister
		.Register<GameTime>()
		.Register<Debug>()
		.Register<GameWindow>()
		
		// ゲームウィンドウシステムを登録したあとでメインウィンドウを登録
		.Register<MainWindow>()

		// メインウィンドウを登録したあとで ウィンドウハンドルを使うシステムを登録
		.Register<Direct3D>()
		.Register<Input>()
	;
}

void SampleGame::StartSetup(
	const GameSystemCollection::GameSystemInitViewer& _viewer)
{
	//GameWindowHandle hGameWindow
	//{
	//	_viewer.Get<GameWindow>().Create(
	//	{
	//		.title = Game::Title(),
	//		.classStyle = CS_VREDRAW | CS_HREDRAW,
	//		.icon = LoadIcon(nullptr, IDI_APPLICATION),
	//		.iconSmile = LoadIcon(nullptr, IDI_WINLOGO),
	//		.cursor = LoadCursor(nullptr, IDC_ARROW),
	//		.clientStyle = WS_OVERLAPPEDWINDOW,
	//		.clientStyleEx = WS_EX_OVERLAPPEDWINDOW,
	//		.hasMenu = FALSE,
	//		// TODO: スクリーンサイズをinitファイルから読み込む
	//		.windowScreenSize = { 1600, 900 },
	//		.initPosition = { 50, 50 },
	//		.hWndParent = nullptr,
	//	})
	//};
}
