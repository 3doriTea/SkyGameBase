#include "pch\pch.h"
#include "CharaBall.h"
#include "PlayScene.h"

CharaBall::CharaBall(const Vector3& _position, const Vector3& _velocity) : GameObject
{
	[&_position, &_velocity](GameObjectBuilder& _builder)
	{
		_builder
			.AddComponent<GameObjectProperty>()
				.BeginSetter()
					.name("CharaBall")
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
					.useGravity(true)
					.bounciness(1.0f)
				.EndSetter()
			.AddComponent<ModelMesh>()
				.BeginSetter()
					.fileName("Models/Neko/NekoSphereV2.fbx")
				.EndSetter()
			.AddComponent<MeshRenderer>()
				.BeginSetter()
					.shader("Shader/Simple3D.hlsl")
					.texture("Models/Neko/TextureSphereNeko.png")
				.EndSetter()
		.Build();
	}
}
{
}

CharaBall::~CharaBall()
{
}

void CharaBall::Init()
{
}

void CharaBall::Update()
{
	PlayScene& playScene{ GetScene<PlayScene>() };

	WorldConfig worldConfig{ playScene.GetWorldConfig() };

	Vector3 pos{ Transform().GetPosition() };
	if (pos.x < worldConfig.safeZoneXMin || worldConfig.safeZoneXMax < pos.x)
	{
		RigidBody& rb{ GetComponent<RigidBody>() };
		Vector3 v{ rb.GetVelocity() };
		
		if (pos.x < worldConfig.safeZoneXMin && v.x < 0
		 || worldConfig.safeZoneXMax > pos.x && v.x > 0)
		{
			v.x *= -1.0f;
			rb.SetVelocity(v);
		}
	}
}

void CharaBall::Release()
{
}
