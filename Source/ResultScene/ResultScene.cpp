#include "ResultScene.h"
#include "UI/ScalingCue.h"
#include "UI/FadingCue.h"
#include "UI/DragCircle.h"
#include "UI/ResultPanel.h"


ResultScene::ResultScene(GameScene::Config&& _config) :
	GameScene{ std::move(_config) }
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Start()
{
	Instantiate<ResultPanel>();

	// カーソルが固定されたままになってしまうため明示的に解除
	System().Get<Cursor>().SetCenterLock(false);
	System().Get<Cursor>().SetShow(true);
	System().Get<Cursor>().SetLock(false, {});
}

void ResultScene::Update()
{
}
