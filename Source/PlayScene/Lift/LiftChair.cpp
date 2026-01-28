#include "pch\pch.h"
#include "LiftChair.h"
#include "Lift.h"

namespace
{
	static const float LINE_MARGIN{ 5.0f };
}

LiftChair::LiftChair(const EntityId _lift, const float _beginZ, const bool _beginIsUpping) : GameObject
{
	[&_lift](GameObjectBuilder& _builder)
	{
		_builder
			.AddComponent<GameObjectProperty>()
				.BeginSetter()
					.parent(_lift)
					.name("LiftChair")
				.EndSetter()
			.AddComponent<wtgb::Transform>()
				.BeginSetter()
					//.position({ 0, 10, 50 })
				.EndSetter()
			.AddComponent<ModelMesh>()
				.BeginSetter()
					.fileName("Models/LiftChair/LiftChair.fbx")
				.EndSetter()
			.AddComponent<MeshRenderer>()
				.BeginSetter()
					.shader("Shader/Simple3D.hlsl")
				.EndSetter()
		.Build();
	},
},
	lift_{ _lift },
	positionZ_{ _beginZ },
	isUpping_{ _beginIsUpping },
	isRotating_{ false }
{
}

LiftChair::~LiftChair()
{
}

void LiftChair::Init()
{
}

void LiftChair::Update()
{
	const float dt{ System().Get<GameTime>().GetDeltaTime() };

	Lift* pLift{ dynamic_cast<Lift*>(FindGameObject(lift_)) };
	if (pLift)
	{  // リフト本体が見つかる前提
		if (isRotating_)
		{  // 転回中なら
			Vector3 position{};
			float z{ Transform().GetPositionWorld().z };
			if (pLift->TryGetLinePosition(z, &position))
			{
				EndUTurn();
			}
			return;
		}


		float move{ pLift->GetRotationSpeedPerSec() * dt };
		if (isUpping_)
		{
			positionZ_ -= move;
		}
		else
		{
			positionZ_ += move;
		}

		Vector3 position{};
		// リフトライン内にいるかどうか
		bool isInLiftLine{ pLift->TryGetLinePosition(positionZ_, &position) };

		if (isInLiftLine == false)
		{  // リフトラインの外なら転回開始
			StartUTurn();
			return;
		}

		if (isUpping_)
		{
			position.x = -LINE_MARGIN;
		}
		else
		{
			position.x = LINE_MARGIN;
		}
		Transform().SetPosition(position);
	}

	Vector3 worldPos{ Transform().GetPositionWorld() };
}

void LiftChair::Release()
{
}

void LiftChair::StartUTurn()
{
	Lift* pLift{ dynamic_cast<Lift*>(FindGameObject(lift_)) };
	if (pLift == nullptr)
	{
		wassert(false && "リフト本体が見つからないよー");
		return;
	}

	isRotating_ = true;
	EntityId loopPole{};
	if (isUpping_)
	{
		loopPole = pLift->GetLoopPole(Lift::LOOP_POLE_UPPER);
	}
	else
	{
		loopPole = pLift->GetLoopPole(Lift::LOOP_POLE_LOWER);
	}

	GetComponent<GameObjectProperty>().SetParent(loopPole);
}

void LiftChair::EndUTurn()
{
	GetComponent<GameObjectProperty>().SetParent(lift_);

	// 上昇 or 降下 を反転させる
	isUpping_ = !isUpping_;

	isRotating_ = false;
}
