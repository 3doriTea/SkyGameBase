#include "pch\pch.h"
#include "CameraMoveFree.h"

namespace
{
	// デグリをラジアンに変換する
	const float DEG_TO_RAD{ DirectX::XM_2PI / 360.0f };

	// マウススクリーン移動に対する1秒間当たりのカメラ回転角度(Degree)
	const float CAMERA_ROTATE_DEG_SEC{ 10.0f };
	const float UPPER_ANGLE{ 80.0f };
	const float LOWER_ANGLE{ -70.0f };
}

CameraMoveFree::CameraMoveFree()
{
}

CameraMoveFree::~CameraMoveFree()
{
}

void CameraMoveFree::Start()
{
}

void CameraMoveFree::Update(ViewerCached& _system)
{
	float dt{ _system.Get<GameTime>().GetDeltaTime() };
	Camera& camera{ _system.Get<Camera>() };
	Cursor& cursor{ _system.Get<Cursor>() };
	const Input::InputGetter& input{ _system.Get<Input>().Getter() };

	if (input.IsKeyDown(KeyCode::R))
	{
		SetMode(Mode::GamePlay);
		return;
	}

	// マウス移動量をカメラの角度に適用
	Vector3 angles{ Transform().GetRotation() };


	angles.x += cursor.GetFrameMove().y / 10.0f * dt;

	// 上下の角度に制限を付ける
	if (angles.x < DEG_TO_RAD * LOWER_ANGLE)
	{
		angles.x = DEG_TO_RAD * LOWER_ANGLE;
	}
	if (angles.x > DEG_TO_RAD * UPPER_ANGLE)
	{
		angles.x = DEG_TO_RAD * UPPER_ANGLE;
	}

	angles.y += cursor.GetFrameMove().x / 10.0f * dt;

	Transform().SetRotation(angles);

	if (input.IsKey(KeyCode::LeftShift))
	{
		speedBoost_ += dt;
	}
	else
	{
		speedBoost_ = 0.0f;
	}

	Vector3 cameraPos{ Transform().GetPosition() };

	Vector3 move{ Vector3::Zero() };

	move.x += (input.IsKey(KeyCode::D) ? 1.0f : 0.0f + input.IsKey(KeyCode::A) ? -1.0f : 0.0f);
	move.y += (input.IsKey(KeyCode::E) ? 1.0f : 0.0f + input.IsKey(KeyCode::Q) ? -1.0f : 0.0f);
	move.z += (input.IsKey(KeyCode::W) ? 1.0f : 0.0f + input.IsKey(KeyCode::S) ? -1.0f : 0.0f);

	Vector3 dir{ Transform().GetForward() };

	//LOGFLN("move({},{},{})", move.x, move.y, move.z);
	LOGFLN("dir({},{},{})", dir.x, dir.y, dir.z);

	cameraPos = cameraPos + DirectX::XMVector3TransformCoord(move * (dt * (10.0f + (10.0f * speedBoost_))), Transform().GetNormalMatrix());

	Transform().SetPosition(cameraPos);

	camera.targetPosition_ = Transform().GetForward() + Transform().GetPosition();
	camera.position_ = Transform().GetPosition();
}

void CameraMoveFree::End()
{
}
