#include "pch\pch.h"
#include "SampleGame.h"

#include "GameSystem/GameTime.h"
#include "GameSystem/Alarm.h"
#include "GameSystem/Debug.h"
#include "GameSystem/Direct3D.h"
#include "GameSystem/GameWindow.h"
#include "GameSystem/Cursor.h"
#include "GameSystem/Input.h"
#include "GameSystem/SceneManager.h"
#include "GameSystem/ComponentManager.h"

#include "GameSystem/ImGuiSystem.h"

#include "GameSystem/DirectionalLight.h"
#include "GameSystem/Rendering.h"
#include "GameSystem/ResourceSystem.h"
#include "GameSystem/Model.h"

// オリジナルゲームシステム
#include "Systems/MainWindow.h"
#include "Systems/FirstSceneRegister.h"
#include "Systems/CPItemAnim.h"
#include "Systems/ScoreManager.h"

// ベースが用意しているコンポーネントプール
#include "GameSystem/CPGameObject.h"
#include "GameSystem/CPGameObjectProperty.h"
#include "GameSystem/CPTransform.h"
#include "GameSystem/CPModelMesh.h"
#include "GameSystem/CPMeshRenderer.h"
#include "GameSystem/CPCollider.h"
#include "GameSystem/CPRigidBody.h"


#include "GameSystem/Audio.h"

#include "GameSystem/Camera.h"

#include "GameSystem/Canvas.h"

#include "GameSystem/Path.h"
#include "GameSystem/ShaderCompile.h"

#include "GameSystem/Scriptable.h"
// MEMO: 大量のinclude↑が発生し管理が大変
//     : → 解決方法 @00


using namespace wtgb;

void SampleGame::StartRegister(
	const GameSystemCollection::GameSystemAdder& _gameSystemRegister)
{
	// TODO: 登録順番が厳しいところが難儀
	// MEMO: オリジナルのシステムを登録するユーザからするとここは不便
	//     : → Jsonで登録するように変更すべき

	_gameSystemRegister
		.Register<GameTime>()
		.Register<Alarm>()
		.Register<Path>()
		.Register<GameWindow>()

		// ゲームウィンドウシステムを登録したあとでメインウィンドウを登録
		.Register<MainWindow>()

		// メインウィンドウを登録したあとで ウィンドウハンドルを使うシステムを登録
		.Register<Direct3D>()

		// ImGui
		.Register<ImGuiSystem>()

		// 入力系
		.Register<Cursor>()
		.Register<Input>()

		.Register<CPParameter>()
		// ↑ゲームオブジェクトの読み込みに使うもの↑

		.Register<SceneManager>()
		.Register<ResourceSystem>()
		
		.Register<ShaderCompile>()
		.Register<Model>()

		// シーンマネージを登録したあとで最初のシーンを登録
		.Register<FirstSceneRegister>()

		// NOTE: ComponentManagerを追加してから 各ComponentPoolシステムを追加する
		.Register<ComponentManager>()

		// NOTE: ComponentManagerを追加した次にスクリプタブルを追加する
		.Register<Scriptable>()

		// オリジナルコンポーネント
		.Register<CPItemAnim>()

		.Register<CPGameObject>()
		.Register<CPGameObjectProperty>()
		.Register<CPTransform>()

		// 物理演算系
		.Register<CPCollider>()
		.Register<CPRigidBody>()

		// 描画系
		.Register<Camera>()
		.Register<DirectionalLight>()
		.Register<CPModelMesh>()
		.Register<CPMeshRenderer>()
		.Register<Canvas>()  // UIの描画は3D描画の後に！

		.Register<Rendering>()

		.Register<Audio>()

		// スコア系
		.Register<ScoreManager>()

		// デバッグ系は一番最後
		.Register<Debug>()
	;
}
