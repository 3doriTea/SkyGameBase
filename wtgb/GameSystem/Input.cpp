#include "pch\pch.h"
#include "Input.h"
#include "Input/InputResource.h"

#include "GameSystem/GameWindow.h"

using namespace wtgb;

namespace
{
}

wtgb::Input::Input() :
	pResource_{ nullptr }
{
}

wtgb::Input::~Input()
{
	SAFE_DELETE(pResource_);
}

wtgb::Result wtgb::Input::Init(const Viewer& _viewer)
{
	const InputResource::Config CONFIG
	{
		.hWnd = _viewer.Get<GameWindow>().GetMainWindowHandle(),
		.cooperativeLevelFlag = DISCL_NONEXCLUSIVE | DISCL_BACKGROUND,
	};
	pResource_ = new InputResource{ CONFIG };
	pResource_->CallInit();

	return Result::Code::Ok;
}

void wtgb::Input::Update()
{
}

void wtgb::Input::End()
{
	pResource_->CallRelease();
}

bool wtgb::Input::InputData::IsKey(const KeyCode _keyCode)
{
	return false;
}

bool wtgb::Input::InputData::IsKeyDown(const KeyCode _keyCode)
{
	return false;
}

bool wtgb::Input::InputData::IsKeyUp(const KeyCode _keyCode)
{
	return false;
}
