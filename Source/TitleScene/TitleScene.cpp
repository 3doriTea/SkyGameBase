#include "pch/pch.h"
#include "TitleScene.h"

#include "TitleMountain.h"
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
	Instantiate<TitleMountain>();

	Instantiate<SMFPlayer>("Sound/entertainer.mid");

	EntityId dragCircle{ Instantiate<DragCircle>() };
	Instantiate<TitleNeco>(dragCircle);

	System().Get<Camera>().position_ = { 0, 110, -460.0f };
	System().Get<Camera>().targetPosition_ = { 0, 0, 0 };
}

void TitleScene::Update()
{
}
