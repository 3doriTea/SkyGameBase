#include "pch\pch.h"
#include "PlayScene.h"

#include "State/PlayState.h"
#include "WaterSphere.h"
#include "Player.h"
#include "CameraController.h"
#include "../TitleScene/TitleScene.h"
#include "StageLine.h"
#include "TestBillBoard.h"
#include "StageObjectManager.h"
#include "ControlUI.h"
#include "LiftStructure.h"
#include "SkySphere/SkySphere.h"

#include "SMF/SMFPlayer.h"
#include "DropCloud.h"
#include "UI/CountDown.h"
#include "UI/SpeedMessage.h"
#include "SpeedController.h"

#include "Utility/Mathf.h"
#include "UI/MiniChara.h"
#include "UI/MiniCharaManager.h"

#include "Debugger.h"
#include "DragArrowAxis.h"
#include "UI/DragArrow.h"

#include "Systems/ScoreManager.h"
#include "wtgb/GameSystem/DirectionalLight.h"

#include "FlighterController.h"


PlayScene::PlayScene(GameScene::Config&& _config) :
	GameScene{ std::move(_config) },
	worldConfig_
	{
		.safeZoneXMin = 0.0f,
		.safeZoneXMax = 400.0f,
		.eggGetDistance = 10.0f,
		.lightDirection = { -6.74646f, -15.585419f, 26.661987f },
	}
{
}

PlayScene::~PlayScene()
{
}

static EntityId player{};
static EntityId camera{};
static Vector3 pPos{};
static bool isPlayerFixied{};
void PlayScene::Start()
{
	EntityId playState{ Instantiate<PlayState>() };

	// シーンが始まったらスコアをリセットする
	System().Get<ScoreManager>().ResetGameScore();

	Instantiate<Debugger>();

	Instantiate<ControlUI>();
	Instantiate<CountDown>();

	EntityId stageLine{ Instantiate<StageLine>() };

	EntityId smfPlayer{ Instantiate<SMFPlayer>("Sound/entertainer.mid") };

	EntityId liftStructure{ Instantiate<LiftStructure>(stageLine, 10.0f) };
	
	float startPositionX{ Mathf::Lerp(worldConfig_.safeZoneXMin, worldConfig_.safeZoneXMax, 0.5f) };

	player = { Instantiate<Player>(INVALID_ENTITY, Vector3{ startPositionX, 30.0f, 5.0f }, playState) };
	Instantiate<FlighterController>(liftStructure, player);
	Instantiate<StageObjectManager>(stageLine, player, playState);
	EntityId dragArrowAxis{ Instantiate<DragArrowAxis>(player) };
	EntityId dragArrow{ Instantiate<DragArrow>(dragArrowAxis) };
	camera = Instantiate<CameraController>(dragArrowAxis, dragArrow);

	EntityId miniCharaManager{ Instantiate<MiniCharaManager>(smfPlayer) };

	EntityId speedController{ Instantiate<SpeedController>(player) };
	EntityId dropCloud{ Instantiate<DropCloud>(smfPlayer, player, stageLine, playState, speedController, miniCharaManager) };

	Instantiate<SpeedMessage>(speedController);

	Instantiate<SkySphere>(camera);
	
	System().Get<DirectionalLight>()
		.SetDirection(worldConfig_.lightDirection);

	// TODO: お試し↓
	//Instantiate<MiniChara>(dropCloud, smfPlayer, MiniCharaType::Monkitty);

	// TODO: 当たったら倒れる看板を作る
}

void PlayScene::Update()
{
	const Input::InputGetter& input{ System().Get<Input>().Getter() };
	if (input.IsKeyDown(KeyCode::F))
	{
		System().Get<SceneManager>().Move<TitleScene>();
	}
	if (input.IsKeyDown(KeyCode::R))
	{
		System().Get<SceneManager>().Move<PlayScene>();
	}

	// 左コントロール押しながらエスケープでゲームを閉じる
	if (input.IsKeyDown(KeyCode::Escape)
		&& input.IsKey(KeyCode::LeftControl))
	{
		Game::Exit();
	}

	const float DT = System().Get<GameTime>().GetDeltaTime();

#ifdef _DEBUG_DISABLED
	//static float v[3]{ -29.231293, -34.184677, 41.512207 };
	static float v[3]{ -6.74646f, -15.585419f, 26.661987f };
	/*ImGui::Begin("Direction");
	ImGui::InputFloat3("direction", v);
	ImGui::End();*/
	System().Get<DirectionalLight>()
		.SetDirection({ v[0], v[1], v[2] });

	static bool isActive{ false };

	if (input.IsKeyDown(KeyCode::G))
	{
		isActive = !isActive;
		CPGameObject& cpGameObject{ System().Get<CPGameObject>() };
	}

	if (input.IsKeyDown(KeyCode::H))
	{
		isPlayerFixied = !isPlayerFixied;
		CPGameObject& cpGameObject{ System().Get<CPGameObject>() };
		pPos = cpGameObject.FindGameObject(player)->Transform().GetPosition();
	}
	
	if (isActive)
	{
		CPGameObject& cpGameObject{ System().Get<CPGameObject>() };
		Vector3 cPos = cpGameObject.FindGameObject(camera)->Transform().GetPosition();
		Vector3 diff = pPos - cPos;
		v[Vector3::AT_X] = diff.x;
		v[Vector3::AT_Y] = diff.y;
		v[Vector3::AT_Z] = diff.z;
	}

	if (isPlayerFixied)
	{
		CPGameObject& cpGameObject{ System().Get<CPGameObject>() };
		cpGameObject.FindGameObject(player)->Transform().SetPosition(pPos);
	}

	LOGFLN("light = {}, {}, {}", v[0], v[1], v[2]);
#endif
}
