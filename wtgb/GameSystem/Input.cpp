#include "pch\pch.h"
#include "Input.h"
#include "Input/InputResource.h"

#include "GameSystem/GameWindow.h"


using namespace wtgb;

using Check = InputChecker;

namespace
{
}

wtgb::Input::Input() :
	mouseUpdater_{ this },
	inputGetter_{ this },
	pResource_{ nullptr },
	inputData_{},  // MEMO: 念のため初期化
	isKeyPress_
	{
		InputChecker::GenIsPress<InputData::KeyBoardStateArray, KeyCode>(
			inputData_.keyBoardState_)
	},
	isKeyDown_
	{
		InputChecker::GenIsDown<InputData::KeyBoardStateArray, KeyCode>(
			inputData_.keyBoardState_,
			inputData_.keyBoardStatePrev_)
	},
	isKeyUp_
	{
		InputChecker::GenIsUp<InputData::KeyBoardStateArray, KeyCode>(
			inputData_.keyBoardState_,
			inputData_.keyBoardStatePrev_)
	}
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
	inputData_.mousePositionPrev_ = inputData_.mousePosition_;
	inputData_.keyBoardStatePrev_ = inputData_.keyBoardState_;
	inputData_.mouseStatePrev_ = inputData_.mouseState_;

	pResource_->GetKeyDevice()->Acquire();
	pResource_->GetKeyDevice()->GetDeviceState(
		static_cast<DWORD>(inputData_.keyBoardState_.size()),
		inputData_.keyBoardState_.data());

	pResource_->GetMouseDevice()->Acquire();
	pResource_->GetMouseDevice()->GetDeviceState(
		sizeof(inputData_.mouseState_),
		&inputData_.mouseState_);
}

void wtgb::Input::End()
{
	pResource_->CallRelease();
}

bool wtgb::Input::InputGetter::IsKey(const KeyCode _keyCode) const
{
	// MEMO: 以下の書き方が冗長だと考え、改良しました
	//     : InputData& data{ GetAccess()->inputData_ };
	//     : return data.keyBoardState_[static_cast<int>(_keyCode)];
	return GetAccess()->isKeyPress_(_keyCode);
}

bool wtgb::Input::InputGetter::IsKeyDown(const KeyCode _keyCode) const
{
	return GetAccess()->isKeyDown_(_keyCode);
}

bool wtgb::Input::InputGetter::IsKeyUp(const KeyCode _keyCode) const
{
	return GetAccess()->isKeyUp_(_keyCode);
}

bool wtgb::Input::InputGetter::IsMouse(const MouseCode _mouseCode) const
{
	InputData& inputData{ GetAccess()->inputData_ };
	if (inputData.mouseState_.rgbButtons[static_cast<int>(_mouseCode)])
	{
		return true;
	}
	return false;
}

bool wtgb::Input::InputGetter::IsMouseDown(const MouseCode _mouseCode) const
{
	InputData& inputData{ GetAccess()->inputData_ };
	if (inputData.mouseState_.rgbButtons[static_cast<int>(_mouseCode)]
		&& !inputData.mouseStatePrev_.rgbButtons[static_cast<int>(_mouseCode)])
	{
		return true;
	}
	return false;
}

bool wtgb::Input::InputGetter::IsMouseUp(const MouseCode _mouseCode) const
{
	InputData& inputData{ GetAccess()->inputData_ };
	if (!inputData.mouseState_.rgbButtons[static_cast<int>(_mouseCode)]
		&& inputData.mouseStatePrev_.rgbButtons[static_cast<int>(_mouseCode)])
	{
		return true;
	}
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
