#include "pch\pch.h"
#include "WaterSphere.h"

namespace
{
	const float DEAD_ZONE_X_MIN{ -0.5f };
	const float DEAD_ZONE_X_MAX{ 300.5f };
}

WaterSphere::WaterSphere(const Vector3 _localPos) : GameObject
{
	[this, &_localPos](GameObjectBuilder& _builder) -> void
	{
		_builder
		.AddComponent<GameObjectProperty>()
			.BeginSetter()
				.name("WaterSphere")
			.EndSetter()
		.AddComponent<wtgb::Transform>()
			.BeginSetter()
				.position(_localPos)
			.EndSetter()
		.AddComponent<ModelMesh>()
			.BeginSetter()
				.fileName("Models/Sphere/Sphere.fbx")
			.EndSetter()
		.AddComponent<MeshRenderer>()
			.BeginSetter()
				.shader("Shader/WaterBall.hlsl")
			.EndSetter()
		.AddComponent<RigidBody>()
			.BeginSetter()
				.bounciness(1.0f)
				.useGravity(true)
			.EndSetter()
		.AddComponent<Collider>()
			.BeginSetter()
				.colliderType(Collider::Type::Sphere)
			.EndSetter()
		.Build();
	}
}
{
}

WaterSphere::~WaterSphere()
{
}

void WaterSphere::Init()
{
}

void WaterSphere::Update()
{
	Vector3 pos{ Transform().GetPosition() };
	if (pos.x < DEAD_ZONE_X_MIN || DEAD_ZONE_X_MAX < pos.x)
	{
		//DestroyMe();
	}
}

void WaterSphere::Release()
{
}
