#include "pch\pch.h"
#include "CameraController.h"

namespace
{
	// デグリをラジアンに変換する
	const float DEG_TO_RAD{ DirectX::XM_2PI / 360.0f };

	// マウススクリーン移動に対する1秒間当たりのカメラ回転角度(Degree)
	const float CAMERA_ROTATE_DEG_SEC{ 10.0f };
	const float UPPER_ANGLE{ 80.0f };
	const float LOWER_ANGLE{ -70.0f };
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
		.AddComponent<RigidBody>()
			.BeginSetter()
			.EndSetter()
		.AddComponent<Collider>()
			.BeginSetter()
				.colliderType(Collider::Type::Sphere)
			.EndSetter()
		.Build();
	}
},
	speedBoost_{ 0.0f },
	mode_{ Mode::Free }
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
	/*RigidBody& rb{ GetComponent<RigidBody>() };
	LOGFLN("当たって{}", rb.IsHit() ? "いる" : "いない");

	std::vector<Collider*> hitColliders{};
	rb.GetHitColliders(&hitColliders);

	for (Collider* pColl : hitColliders)
	{
		if (pColl)
		{
			LOGFLN("Type:{}", pColl->GetColliderType() == Collider::Type::Sphere ? "球体" : "セクション");
		}
	}*/

	switch (mode_)
	{
	case CameraController::Mode::Free:
		UpdateFree();
		break;
	case CameraController::Mode::GamePlay:
		UpdateGamePlay();
		break;
	default:
		wassert(false && "未処理のカメラモード");
		break;
	}
}

void CameraController::UpdateFree()
{
	float dt{ System().Get<GameTime>().GetDeltaTime() };
	Camera& camera{ System().Get<Camera>() };
	Cursor& cursor{ System().Get<Cursor>() };
	const Input::InputGetter& input{ System().Get<Input>().Getter() };


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

	LOGFLN("move({},{},{})", move.x, move.y, move.z);

	cameraPos = cameraPos + DirectX::XMVector3TransformCoord(move * (dt * (10.0f + (10.0f * speedBoost_))), Transform().GetNormalMatrix());

	Transform().SetPosition(cameraPos);

	camera.targetPosition_ = Transform().GetForward() + Transform().GetPosition();
	camera.position_ = Transform().GetPosition();
}

void CameraController::UpdateGamePlay()
{
}
