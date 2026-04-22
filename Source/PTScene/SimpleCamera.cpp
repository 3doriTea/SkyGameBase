#include "SimpleCamera.h"

SimpleCamera::SimpleCamera() :
	GameObject{ "PT/SimpleCamera.json" },
	moveSpeedPerSec_{ 0.0f },
	moveAnglePerSecRad_{ 0.0f }
{
}

SimpleCamera::~SimpleCamera()
{
}

void SimpleCamera::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());
}

void SimpleCamera::Update()
{
	const float DT{ System().Get<GameTime>().GetDeltaTime() };
	const auto& input{ System().Get<Input>().Getter() };
	auto& camera{ System().Get<Camera>() };

	UpdatePosition();

	UpdateAngle();

	camera.position_ = Transform().GetPosition();
	camera.targetPosition_ = camera.position_ + Transform().GetForward();
}

void SimpleCamera::Release()
{
}

void SimpleCamera::OnLoadParam(const json& _json)
{
	moveSpeedPerSec_ = _json.value("moveSpeedPerSec", 30.0f);
	moveAnglePerSecRad_ = _json.value("moveAnglePerSecRad", 0.52359877559f);
}

bool SimpleCamera::UpdatePosition()
{
	const float DT{ System().Get<GameTime>().GetDeltaTime() };
	const auto& input{ System().Get<Input>().Getter() };

	Vector3 move{};
	if (input.IsKey(KeyCode::W))
	{
		move.z += moveSpeedPerSec_;
	}
	if (input.IsKey(KeyCode::S))
	{
		move.z -= moveSpeedPerSec_;
	}
	if (input.IsKey(KeyCode::A))
	{
		move.x -= moveSpeedPerSec_;
	}
	if (input.IsKey(KeyCode::D))
	{
		move.x += moveSpeedPerSec_;
	}
	if (input.IsKey(KeyCode::Q))
	{
		move.y -= moveSpeedPerSec_;
	}
	if (input.IsKey(KeyCode::E))
	{
		move.y += moveSpeedPerSec_;
	}

	Vector3 position{ Transform().GetPosition() };
	Vector3 moveWorld{ DirectX::XMVector3TransformCoord(move, Transform().GetNormalMatrix()) };
	position = position + moveWorld * DT;
	Transform().SetPosition(position);

	return true;  // TOOD: 移動しなかったらfalseを返すようにする
}

bool SimpleCamera::UpdateAngle()
{
	const float DT{ System().Get<GameTime>().GetDeltaTime() };
	const auto& input{ System().Get<Input>().Getter() };
	
	Vector3 moveAngle{};
	if (input.IsKey(KeyCode::Down))
	{
		moveAngle.x += moveAnglePerSecRad_;
	}
	if (input.IsKey(KeyCode::Up))
	{
		moveAngle.x -= moveAnglePerSecRad_;
	}
	if (input.IsKey(KeyCode::Right))
	{
		moveAngle.y += moveAnglePerSecRad_;
	}
	if (input.IsKey(KeyCode::Left))
	{
		moveAngle.y -= moveAnglePerSecRad_;
	}
	
	Vector3 angle{ Transform().GetRotation() };
	angle = angle + moveAngle * DT;
	Transform().SetRotation(angle);

	return true;  // TODO: 回転しなかったらfalseを返すようにする
}
