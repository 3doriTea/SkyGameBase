#include "pch\pch.h"
#include "SampleGame.h"

#include "GameSystem/GameTime.h"
#include "GameSystem/Debug.h"
#include "GameSystem/Direct3D.h"
#include "GameSystem/GameWindow.h"
#include "GameSystem/Input.h"
#include "GameSystem/SceneManager.h"
#include "GameSystem/ComponentManager.h"

#include "GameSystem/Rendering.h"
#include "GameSystem/ResourceSystem.h"

#include "Systems/MainWindow.h"
#include "Systems/FirstSceneRegister.h"

#include "GameSystem/CPGameObject.h"
#include "GameSystem/CPGameObjectProperty.h"
#include "GameSystem/CPTransform.h"
#include "GameSystem/CPModelMesh.h"
#include "GameSystem/CPMeshRenderer.h"

#include "GameSystem/Path.h"

using namespace wtgb;

void SampleGame::StartRegister(
	const GameSystemCollection::GameSystemAdder& _gameSystemRegister)
{
	// TODO: 登録順番が厳しいところが難儀 ユーザからするとここは不便
	_gameSystemRegister
		.Register<GameTime>()
		.Register<Path>()
		.Register<Debug>()
		.Register<GameWindow>()
		
		// ゲームウィンドウシステムを登録したあとでメインウィンドウを登録
		.Register<MainWindow>()

		// メインウィンドウを登録したあとで ウィンドウハンドルを使うシステムを登録
		.Register<Direct3D>()
		.Register<Input>()

		.Register<SceneManager>()
		.Register<ResourceSystem>()
		
		// シーンマネージを登録したあとで最初のシーンを登録
		.Register<FirstSceneRegister>()

		.Register<ComponentManager>()

		.Register<CPGameObject>()
		.Register<CPGameObjectProperty>()
		.Register<CPTransform>()

		// 描画系
		.Register<CPModelMesh>()
		.Register<CPMeshRenderer>()


		.Register<Rendering>()
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
