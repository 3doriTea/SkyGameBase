#include "pch\pch.h"
#include "LiftLoop.h"
#include "../LiftStructure.h"

namespace
{
	static const Vector3 SCALE{ 0.4f, 0.4f, 0.4f };
}

LiftLoop::LiftLoop(const Vector3& _position, const EntityId _structure) : GameObject
	{
		[&_position](GameObjectBuilder& _builder)
		{
			_builder
				.AddComponent<GameObjectProperty>()
					.BeginSetter()
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
	structure_{ _structure }
{
}

void LiftLoop::Update()
{
	const float dt{ System().Get<GameTime>().GetDeltaTime() };
	LiftStructure* pStructure{ FindGameObject<LiftStructure>(structure_) };
	wassert(pStructure && "リフト構造物が見つからなかった！");

	if (pStructure)
	{
		Vector3 rot{ Transform().GetRotation() };
		rot.y += pStructure->GetRotationSpeedPerSec() * dt;
		Transform().SetRotation(rot);
	}
}
