#include "pch\pch.h"
#include "FirstSceneRegister.h"
#include "GameSystem/SceneManager.h"

// 最初に起動するシーン候補のインクルードたち
#include "TitleScene/TitleScene.h"
#include "PlayScene/PlayScene.h"
#include "ResultScene/ResultScene.h"
#include "StageSelectScene/StageSelectScene.h"
#include "../SampleScene/SampleScene.h"
#include "../PTScene/PTScene.h"

wtgb::Result FirstSceneRegister::Init(const ViewerInit& _viewer)
{
	_viewer.Get<SceneManager>().Move<TitleScene>();

	return Result::Code::Ok;
}
