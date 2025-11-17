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

	if (input.IsMouseDown(MouseCode::Left))
	{
		cursor.SetCenterLock(true);
	}
	if (input.IsKeyDown(KeyCode::Escape))
	{
		cursor.SetCenterLock(false);
	}


	//Vector2Int currMousePos{ input.GetMousePosition() };
	//Vector2Int mouseMove{ currMousePos - prevMousePos_ };
	//prevMousePos_ = currMousePos;

	// マウス移動量をカメラの角度に適用
	Vector3 angles{ Transform().GetRotation() };
	angles.x -= cursor.GetFrameMove().y / 1000.0f;
	angles.y += cursor.GetFrameMove().x / 1000.0f;
	Transform().SetRotation(angles);

	Vector3 cameraPos{ Transform().GetPosition() };

	cameraPos.x += (input.IsKey(KeyCode::D) ? 1.0f : 0.0f + input.IsKey(KeyCode::A) ? -1.0f : 0.0f) * dt * 10.0f;
	cameraPos.y += (input.IsKey(KeyCode::E) ? 1.0f : 0.0f + input.IsKey(KeyCode::Q) ? -1.0f : 0.0f) * dt * 10.0f;
	cameraPos.z += (input.IsKey(KeyCode::W) ? 1.0f : 0.0f + input.IsKey(KeyCode::S) ? -1.0f : 0.0f) * dt * 10.0f;

	Transform().SetPosition(cameraPos);

	camera.targetPosition_ = Transform().GetForward() + Transform().GetPosition();
	camera.position_ = Transform().GetPosition();
}
