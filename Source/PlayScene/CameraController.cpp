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
	Camera& camera{ System().Get<Camera>() };
	const Input::InputGetter& input{ System().Get<Input>().Getter() };

	Vector2Int currMousePos{ input.GetMousePosition() };
	Vector2Int mouseMove{ currMousePos - prevMousePos_ };
	prevMousePos_ = currMousePos;

	// マウス移動量をカメラの角度に適用
	Vector3 angles{ Transform().GetRotation() };
	angles.x -= mouseMove.y;
	angles.y += mouseMove.x;
	Transform().SetRotation(angles);

	camera.targetPosition_ = Transform().GetForward() + Transform().GetPosition();
}
