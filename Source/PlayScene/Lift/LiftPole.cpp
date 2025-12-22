#include "pch\pch.h"
#include "LiftPole.h"

LiftPole::LiftPole(const Vector3& _position, const EntityId _lift) : GameObject
{
	[&_position, &_lift](GameObjectBuilder& _builder)
	{
		_builder
			.AddComponent<GameObjectProperty>()
				.BeginSetter()
					.parent(_lift)
					.name("LiftPole")
				.EndSetter()
			.AddComponent<wtgb::Transform>()
				.BeginSetter()
					.position(_position)
				.EndSetter()
			.AddComponent<ModelMesh>()
				.BeginSetter()
					.fileName("Models/LiftPole/LiftPole.fbx")
				.EndSetter()
			.AddComponent<MeshRenderer>()
				.BeginSetter()
					.shader("Shader/Simple3D.hlsl")
				.EndSetter()
		.Build();
	}
}
{
}
