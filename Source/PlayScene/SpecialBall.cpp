#include "pch/pch.h"
#include "SpecialBall.h"

namespace
{
	const float SAFE_ZONE_X_MIN{ 0.0f };
	const float SAFE_ZONE_X_MAX{ 400.0f };
}

SpecialBall::SpecialBall(const Vector3& _position, const Vector3& _velocity) : GameObject
{
	[&_position, &_velocity](GameObjectBuilder& _builder)
	{
		_builder
			.AddComponent<GameObjectProperty>()
				.BeginSetter()
					.name("SpecialBall")
				.EndSetter()
			.AddComponent<wtgb::Transform>()
				.BeginSetter()
					.position(_position)
				.EndSetter()
			.AddComponent<Collider>()
				.BeginSetter()
					.colliderType(Collider::Type::Sphere)
				.EndSetter()
			.AddComponent<RigidBody>()
				.BeginSetter()
					.velocity(_velocity)
					.useGravity(false)
					.bounciness(1.0f)
				.EndSetter()
			.AddComponent<ModelMesh>()
				.BeginSetter()
					.fileName("Models/Sphere/Sphere.fbx")
				.EndSetter()
			.AddComponent<MeshRenderer>()
				.BeginSetter()
					.shader("Shader/SpecialBall.hlsl")
				.EndSetter()
		.Build();
	}
}
{
}

SpecialBall::~SpecialBall()
{
}

void SpecialBall::Init()
{
}

void SpecialBall::Update()
{
	Vector3 pos{ Transform().GetPosition() };
	if (pos.x < SAFE_ZONE_X_MIN || SAFE_ZONE_X_MAX < pos.x)
	{
		DestroyMe();
	}
}

void SpecialBall::Release()
{
}
