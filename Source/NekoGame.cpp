#include "pch\pch.h"
#include "NekoGame.h"

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
#include "GameSystem/PostProcessing.h"
// オリジナルゲームシステム
#include "Systems/MainWindow.h"
#include "Systems/FirstSceneRegister.h"
#include "Systems/CPItemAnim.h"
#include "Systems/ScoreManager.h"
#include "Systems/FaderSystem.h"
#include "Systems/ConstantBufferSender.h"
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


using namespace wtgb;

void NekoGame::StartRegister(
	const GameSystemCollection::GameSystemAdder& _gameSystemRegister)
{
	_gameSystemRegister
		.Register<GameTime>()
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
		.Register<Alarm>()  // ゲームオブジェクトの更新の次
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
		.Register<PostProcessing>()        // 3D描画の後処理
		.Register<Canvas>()                // UIの描画は3D描画の後に！
		.Register<FaderSystem>()           // フェーダの描画はUI描画の後に！
		.Register<ConstantBufferSender>()  // 念のため描画直前にコンスタントバッファ

		.Register<Rendering>()

		.Register<Audio>()

		// スコア系
		.Register<ScoreManager>()

		// NOTE: デバッグ系は一番最後
		.Register<Debug>()
	;
}
