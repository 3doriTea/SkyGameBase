#include "pch\pch.h"
#include "FirstSceneRegister.h"
#include "GameSystem/SceneManager.h"

#include "TitleScene/TitleScene.h"
#include "../SampleScene/SampleScene.h"

wtgb::Result FirstSceneRegister::Init(const ViewerInit& _viewer)
{
	_viewer.Get<SceneManager>().Move<TitleScene>();

	return Result::Code::Ok;
}
