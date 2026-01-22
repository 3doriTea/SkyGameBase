#include "pch\pch.h"
#include "CameraController.h"
#include "CameraController/CameraMoveFree.h"
#include "CameraController/CameraMovePlay.h"


CameraController::CameraController() :
	GameObject{ "Play/CameraController.json" },
mode_{ Mode::Play },
lookTarget_{ INVALID_ENTITY },
pCameraMove_{ nullptr }
{
}

CameraController::~CameraController()
{
}

void CameraController::Init()
{
	SetMode(Mode::Play);  // 最初は自由カメラ
}

void CameraController::Update()
{
	const Input::InputGetter& input{ System().Get<Input>().Getter() };
	Cursor& cursor{ System().Get<Cursor>() };
	Camera& camera{ System().Get<Camera>() };


	if (input.IsKeyDown(KeyCode::Escape))
	{
		cursor.SetCenterLock(false);
		cursor.SetShow(true);
	}

	pCameraMove_->Update({ System(), GetEntityId() });

	camera.targetPosition_ = Transform().GetPosition() + Transform().GetForward();
	camera.position_ = Transform().GetPosition();

	switch (mode_)
	{
	case CameraController::Mode::Free:
		if (input.IsKeyDown(KeyCode::R))
		{
			SetMode(Mode::Play);
		}
		break;
	case CameraController::Mode::Play:
		if (input.IsKeyDown(KeyCode::R))
		{
			Vector3 rotation{ Transform().GetRotation() };
			rotation.z = 0.0f;
			Transform().SetRotation(rotation);
			SetMode(Mode::Free);
		}
		break;
	default:
		wassert(false && "未処理のカメラモード");
		break;
	}
}

void CameraController::Release()
{
	// しっかり解放
	SAFE_DELETE(pCameraMove_);

	// カーソルの後片付けをしっかり
	const Input::InputGetter& input{ System().Get<Input>().Getter() };
	Cursor& cursor{ System().Get<Cursor>() };
	cursor.SetCenterLock(false);
	cursor.SetShow(true);
}

void CameraController::SetMode(const Mode _mode)
{
	mode_ = _mode;

	if (pCameraMove_)
	{
		pCameraMove_->End({ System(), GetEntityId() });
	}

	SAFE_DELETE(pCameraMove_);
	switch (_mode)
	{
	case Mode::Free:
		pCameraMove_ = new CameraMoveFree{};
		break;
	case Mode::Play:
		pCameraMove_ = new CameraMovePlay{};
		break;
	default:
		wassert(false && "未実装のカメラモード");
		return;
	}

	if (pCameraMove_)
	{
		pCameraMove_->Start({ System(), GetEntityId() });
	}
}
