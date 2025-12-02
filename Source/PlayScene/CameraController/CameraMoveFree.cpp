#include "pch\pch.h"
#include "CameraMoveFree.h"


namespace
{
	// デグリをラジアンに変換する
	const float DEG_TO_RAD{ DirectX::XM_2PI / 360.0f };

	// マウススクリーン移動に対する1秒間当たりのカメラ回転角度(Degree)
	const float CAMERA_ROTATE_DEG_SEC{ 10.0f };
	// カメラ上の角度の制限
	const float UPPER_ANGLE{ 80.0f };
	// カメラ下の角度の制限
	const float LOWER_ANGLE{ -70.0f };

	// 1秒間あたりの移動速度
	const float MOVE_SPEED_PER_SEC{ 10.0f };
}

CameraMoveFree::CameraMoveFree() :
	speedBoost_{ 0.0f }
{
}

CameraMoveFree::~CameraMoveFree()
{
}

void CameraMoveFree::Start(GameObjectReference _ref)
{
	auto [systemView, entityId]{ _ref };

	Cursor& cursor{ systemView.Get<Cursor>() };
	cursor.SetCenterLock(false);
	cursor.SetShow(true);
}

void CameraMoveFree::Update(GameObjectReference _ref)
{
	auto [systemView, entityId]{ _ref };

	float dt{ systemView.Get<GameTime>().GetDeltaTime() };
	Camera& camera{ systemView.Get<Camera>() };
	Cursor& cursor{ systemView.Get<Cursor>() };
	const Input::InputGetter& input{ systemView.Get<Input>().Getter() };
	Transform* pTransform{ systemView.Get<CPTransform>().Get(entityId) };

	// マウスカーソルの制御
	
	if (input.IsMouseDown(MouseCode::Left))
	{
		cursor.SetCenterLock(true);
		cursor.SetShow(false);
		isDragging_ = true;

	}
	if (input.IsMouseUp(MouseCode::Left))
	{
		isDragging_ = false;
	}
	if (input.IsKeyDown(KeyCode::Escape))
	{
		cursor.SetCenterLock(false);
		cursor.SetShow(true);
	}


	// マウス移動量をカメラの角度に適用
	Vector3 angles{ pTransform->GetRotation() };


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

	pTransform->SetRotation(angles);

	if (input.IsKey(KeyCode::LeftShift))
	{
		// 左シフトキー長押しで加速
		speedBoost_ += dt;
	}
	else
	{
		speedBoost_ = 0.0f;
	}

	Vector3 cameraPos{ pTransform->GetPosition() };

	Vector3 move{ Vector3::Zero() };

	move.x += (input.IsKey(KeyCode::D) ? 1.0f : 0.0f + input.IsKey(KeyCode::A) ? -1.0f : 0.0f);
	move.y += (input.IsKey(KeyCode::E) ? 1.0f : 0.0f + input.IsKey(KeyCode::Q) ? -1.0f : 0.0f);
	move.z += (input.IsKey(KeyCode::W) ? 1.0f : 0.0f + input.IsKey(KeyCode::S) ? -1.0f : 0.0f);

	Vector3 dir{ pTransform->GetForward() };

	cameraPos = cameraPos + DirectX::XMVector3TransformCoord(
		move * (dt * (MOVE_SPEED_PER_SEC + (MOVE_SPEED_PER_SEC * speedBoost_))),
		pTransform->GetNormalMatrix());

	pTransform->SetPosition(cameraPos);

	camera.targetPosition_ = pTransform->GetForward() + pTransform->GetPosition();
	camera.position_ = pTransform->GetPosition();
}

void CameraMoveFree::End(GameObjectReference _ref)
{
}
