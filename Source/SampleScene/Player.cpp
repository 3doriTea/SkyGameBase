#include "pch\pch.h"
#include "Player.h"

using namespace wtgb;

Player::Player(const EntityId _parentId, const Vector3 _localPos) : GameObject
{
	[this, &_parentId, &_localPos](GameObjectBuilder& _builder) -> void
	{
		_builder
		.AddComponent<GameObjectProperty>()
			.BeginSetter()
				.name("Player")
				.parent(_parentId)
			.EndSetter()
		.AddComponent<wtgb::Transform>()
			.BeginSetter()
				.position(_localPos)
				.rotation({ 0, 90, 0 })
				.scale({ 1, 1, 1 })
			.EndSetter()
		.AddComponent<ModelMesh>()
			.BeginSetter()
				//.fileName("Models/Oden.fbx")
				//.fileName("Models/TestCube/TestCube.fbx")
				//.fileName("Models/Neko/NekoSphere.fbx")
				.fileName("Models/Neko/NekoSphereV2.fbx")
			.EndSetter()
		.AddComponent<MeshRenderer>()
			.BeginSetter()
				.shader("Shader/Simple3D.hlsl")
				//.texture("Models/TestCube/TestCubeTexture.png")
				//.texture("Models/Oden.jpg")
				.texture("Models/Neko/TextureSphereNeko.png")
				//.texture("Models/TestCube/UVChecker.jpg")
			.EndSetter()
		.AddComponent<RigidBody>()
			.BeginSetter()
				.useGravity(false)
				.useSphereCollider(true)
				.velocity({ 0, 0, 1.0f })
				.angularVelocity({ 0.5f, 0, 0 })
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

Player::~Player()
{
}

void Player::Init()
{
	angle_ = 0.0f;
	//GetComponent<ModelMesh>().Load();
}

void Player::Update()
{
	float dt{ System().Get<GameTime>().GetDeltaTime() };

	return;

	angle_ += DirectX::XM_2PI / 10.0f * dt;
	if (angle_ >= DirectX::XM_2PI)
	{
		angle_ -= DirectX::XM_2PI;
	}

	Vector3 rotation{ Transform().GetRotation() };
	rotation.y = angle_;
	Transform().SetRotation(rotation);

	Transform().SetScale((std::sinf(angle_) * std::sinf(angle_) * 3.0f) * Vector3::One() + Vector3::One());
}
