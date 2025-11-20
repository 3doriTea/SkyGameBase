#include "pch\pch.h"
#include "CameraController.h"

namespace
{
	// マウススクリーン移動に対する1秒間当たりのカメラ回転角度(Degree)
	const float CAMERA_ROTATE_DEG_SEC{ 10.0f };
}

CameraController::CameraController() : GameObject
{
	[this](GameObjectBuilder& _builder) -> void
	{
		_builder
		.AddComponent<GameObjectProperty>()
			.BeginSetter()
				.name("CamCon")
			.EndSetter()
		.AddComponent<wtgb::Transform>()
			.BeginSetter()
				.position({ 0, 0, -10 })
				.rotation(Vector3::Zero())
			.EndSetter()
		.Build();
	}
}
{
}

CameraController::~CameraController()
{
}

void CameraController::Init()
{
}

void CameraController::Update()
{
	float dt{ System().Get<GameTime>().GetDeltaTime() };
	Camera& camera{ System().Get<Camera>() };
	Cursor& cursor{ System().Get<Cursor>() };
	const Input::InputGetter& input{ System().Get<Input>().Getter() };

	//if (input.IsMouseDown(MouseCode::Left))
	if (input.IsKeyDown(KeyCode::B))
	{
		cursor.SetCenterLock(true);
		cursor.SetShow(false);
	}
	if (input.IsKeyDown(KeyCode::Escape))
	{
		cursor.SetCenterLock(false);
		cursor.SetShow(true);
	}

	// マウス移動量をカメラの角度に適用
	Vector3 angles{ Transform().GetRotation() };

	LOGFLN("({}, {})", cursor.GetFrameMove().x, cursor.GetFrameMove().y);

	// angles.x += (DirectX::XM_2PI / 360.0f) * cursor.GetFrameMove().y * 1.0f * dt;
	// angles.y += (DirectX::XM_2PI / 360.0f) * cursor.GetFrameMove().x * 1.0f * dt;

	const float DEG_TO_RAD{ DirectX::XM_2PI / 360.0f };

	angles.x += cursor.GetFrameMove().y / 100.0f * dt;

	if (angles.x < -DEG_TO_RAD * 70.0f)
	{
		angles.x = -DEG_TO_RAD * 70.0f;
	}
	if (angles.x > DEG_TO_RAD * 80.0f)
	{
		angles.x = DEG_TO_RAD * 80.0f;
	}

	LOGFLN("angles.x={}", angles.x);

	angles.y += cursor.GetFrameMove().x / 100.0f * dt;

	/*if (input.IsKey(KeyCode::Up))
	{
		angles.x -= (DirectX::XM_2PI / 360.0f) * 10.0f * dt;
	}
	if (input.IsKey(KeyCode::Down))
	{
		angles.x += (DirectX::XM_2PI / 360.0f) * 10.0f * dt;
	}
	if (input.IsKey(KeyCode::Left))
	{
		angles.x += (DirectX::XM_2PI / 360.0f) * 10.0f * dt;
	}
	if (input.IsKey(KeyCode::Right))
	{
		angles.x -= (DirectX::XM_2PI / 360.0f) * 10.0f * dt;
	}*/

	Transform().SetRotation(angles);

	Vector3 cameraPos{ Transform().GetPosition() };

	cameraPos.x += (input.IsKey(KeyCode::D) ? 1.0f : 0.0f + input.IsKey(KeyCode::A) ? -1.0f : 0.0f) * dt * 10.0f;
	cameraPos.y += (input.IsKey(KeyCode::E) ? 1.0f : 0.0f + input.IsKey(KeyCode::Q) ? -1.0f : 0.0f) * dt * 10.0f;
	cameraPos.z += (input.IsKey(KeyCode::W) ? 1.0f : 0.0f + input.IsKey(KeyCode::S) ? -1.0f : 0.0f) * dt * 10.0f;

	Transform().SetPosition(cameraPos);

	camera.targetPosition_ = Transform().GetForward() + Transform().GetPosition();
	camera.position_ = Transform().GetPosition();
}
