#include "pch\pch.h"
#include "SampleScene.h"

#include "GameSystem/Camera.h"

#include "UI/NumberPlate.h"
#include "TestArrowUI.h"
#include "../PlayScene/Player.h"
#include "../PlayScene/PlayScene.h"
#include "../PlayScene/CameraController.h"
#include "../ResultScene/ResultScene.h"

#include "../TitleScene/TitleNeco.h"

#include "Piano.h"
#include "../SMF/SMFPlayer.h"

#include "../UI/DragCircle.h"

using namespace wtgb;

SampleScene::SampleScene(GameScene::Config&& _config) :
	GameScene{ std::move(_config) }
{
}

void SampleScene::Start()
{
	Instantiate<SMFPlayer>("Sound/entertainer.mid");

	EntityId dragCircle{ Instantiate<DragCircle>() };
	//Instantiate<SMFPlayer>("Sound/gekkou1-rei.MID");
	//Instantiate<SMFPlayer>("Sound/entertainer.mid");
	Instantiate<TitleNeco>(dragCircle);

	System().Get<Camera>().position_ = { 0, 0, -10.0f };
	System().Get<Camera>().targetPosition_ = { 0, 0, 0 };

	//Instantiate<Piano>();

	//EntityId eNumberPlate{ Instantiate<NumberPlate>() };

	//Instantiate<TestArrowUI>(eNumberPlate);

	//EntityId pRoot = Instantiate<Player>(INVALID_ENTITY, Vector3::Zero());
	////pRoot = INVALID_ENTITY;
	//EntityId pChild1 = Instantiate<Player>(pRoot, Vector3{ 3.0f, 2.0f, 0.0 });
	////pChild1 = INVALID_ENTITY;
	//EntityId pChild2 = Instantiate<Player>(pChild1, Vector3{ 3.0f, 2.0f, 0.0 });
	//Instantiate<CameraController>();
}

void SampleScene::Update()
{
	const Input::InputGetter& input{ System().Get<Input>().Getter() };
	if (input.IsKeyDown(KeyCode::F))
	{
		System().Get<SceneManager>().Move<PlayScene>();
	}
}
