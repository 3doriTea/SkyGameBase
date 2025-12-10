#include "SpecialBall.h"

SpecialBall::SpecialBall(const Vector3& _position) : GameObject
{
	[&_position](GameObjectBuilder& _builder)
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
					.bounciness(1.0f)
				.EndSetter()
			.AddComponent<ModelMesh>()
				.BeginSetter()
					.fileName("Model/Sphere.fbx")
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
}

void SpecialBall::Release()
{
}
