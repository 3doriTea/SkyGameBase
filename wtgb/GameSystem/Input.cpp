#include "pch\pch.h"
#include "Input.h"
#include "Input/InputResource.h"

#include "GameSystem/GameWindow.h"

using namespace wtgb;

namespace
{
}

wtgb::Input::Input() :
	mouseUpdater_{ this },
	inputGetter_{ this },
	pResource_{ nullptr },
	inputData_{}  // MEMO: 念のため初期化
{
}

wtgb::Input::~Input()
{
	SAFE_DELETE(pResource_);
}

wtgb::Result wtgb::Input::Init(const ViewerInit& _viewer)
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

void wtgb::Input::Update(const ViewerUpdate& _system)
{
	// TODO: 順番によってマウス移動量がフレーム上書きされる
	inputData_.mousePositionPrev_ = inputData_.mousePosition_;
}

void wtgb::Input::End()
{
	pResource_->CallRelease();
}

bool wtgb::Input::InputGetter::IsKey(const KeyCode _keyCode) const
{
	return false;
}

bool wtgb::Input::InputGetter::IsKeyDown(const KeyCode _keyCode) const
{
	return false;
}

bool wtgb::Input::InputGetter::IsKeyUp(const KeyCode _keyCode) const
{
	return false;
}

void wtgb::Input::MouseUpdater::SetMousePosition(const Vector2Int _position)
{
	InputData& data{ GetAccess()->inputData_ };

	data.mousePosition_ = _position;
}

Vector2Int wtgb::Input::InputGetter::GetMousePosition() const
{
	InputData& data{ GetAccess()->inputData_ };

	return data.mousePosition_;
}

Vector2Int wtgb::Input::InputGetter::GetMouseMove() const
{
	InputData& data{ GetAccess()->inputData_ };

	return data.mousePosition_ - data.mousePositionPrev_;
}
