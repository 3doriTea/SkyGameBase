#include "pch\pch.h"
#include "LiftLoop.h"
#include "Lift.h"

namespace
{
	static const Vector3 SCALE{ 0.4f, 0.4f, 0.4f };
}

LiftLoop::LiftLoop(const Vector3& _position, const EntityId _lift) : GameObject
{
	[&_position, &_lift](GameObjectBuilder& _builder)
	{
		_builder
			.AddComponent<GameObjectProperty>()
				.BeginSetter()
					.parent(_lift)
					.name("LiftLoop")
				.EndSetter()
			.AddComponent<wtgb::Transform>()
				.BeginSetter()
					.position(_position)
					.scale(SCALE)
				.EndSetter()
			.AddComponent<ModelMesh>()
				.BeginSetter()
					.fileName("Models/LiftLoop/LiftLoop.fbx")
				.EndSetter()
			.AddComponent<MeshRenderer>()
				.BeginSetter()
					.shader("Shader/Simple3D.hlsl")
				.EndSetter()
		.Build();
	},
},
	lift_{ _lift }
{
}

void LiftLoop::Update()
{
	const float dt{ System().Get<GameTime>().GetDeltaTime() };
	Lift* lift{ dynamic_cast<Lift*>(FindGameObject(lift_)) };

	wassert(lift && "リフトオブジェクトが見つからなかった！");

	if (lift)
	{
		Vector3 rot{ Transform().GetRotation() };
		rot.y += lift->GetRotationSpeedPerSec() * dt;
		Transform().SetRotation(rot);
	}
}
