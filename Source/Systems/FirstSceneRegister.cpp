#include "pch\pch.h"
#include "FirstSceneRegister.h"
#include "GameSystem/SceneManager.h"
#include "../SampleScene/SampleScene.h"

wtgb::Result FirstSceneRegister::Init(const ViewerInit& _viewer)
{
	_viewer.Get<SceneManager>().Move<SampleScene>();

	return Result::Code::Ok;
}
