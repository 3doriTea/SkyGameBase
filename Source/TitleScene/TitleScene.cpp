#include "pch/pch.h"
#include "TitleScene.h"

#include "TitleNeco.h"
#include "SMF/SMFPlayer.h"
#include "UI/DragCircle.h"

TitleScene::TitleScene() :
	GameScene{{}}
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Start()
{
	Instantiate<SMFPlayer>("Sound/entertainer.mid");

	EntityId dragCircle{ Instantiate<DragCircle>() };
	Instantiate<TitleNeco>(dragCircle);

	System().Get<Camera>().position_ = { 0, 0, -10.0f };
	System().Get<Camera>().targetPosition_ = { 0, 0, 0 };
}

void TitleScene::Update()
{
}
