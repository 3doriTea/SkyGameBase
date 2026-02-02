#include "ResultScene.h"
#include "UI/ScalingCue.h"
#include "UI/FadingCue.h"
#include "UI/DragCircle.h"
#include "UI/ResultPanel.h"


ResultScene::ResultScene() : GameScene
	{ GameScene::Config{} }
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Start()
{
	EntityId dragCircle{ Instantiate<DragCircle>() };
	Instantiate<ResultPanel>(dragCircle);
}

void ResultScene::Update()
{
}
