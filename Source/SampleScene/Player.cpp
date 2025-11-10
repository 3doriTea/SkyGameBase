#include "pch\pch.h"
#include "Player.h"

using namespace wtgb;

Player::Player() : GameObject
{
	[this](GameObjectBuilder& _builder) -> void
	{
		_builder
		.AddComponent<GameObjectProperty>()
			.BeginSetter()
				.name("Player")
			.EndSetter()
		.AddComponent<wtgb::Transform>()
			.BeginSetter()
				.position({ 0, 0, 0 })
				.rotation({ 0, 90, 0 })
				.scale({ 1, 1, 1 })
			.EndSetter()
		.AddComponent<ModelMesh>()
			.BeginSetter()
				//.fileName("Models/Oden.fbx")
				.fileName("Models/TestCube/TestCube.fbx")
			.EndSetter()
		.AddComponent<MeshRenderer>()
			.BeginSetter()
				.shader("Shader/Simple3D.hlsl")
				.texture("Models/TestCube/TestCubeTexture.png")
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
	const Input::InputGetter& input{ System().Get<Input>().Getter() };

	float dt{ System().Get<GameTime>().GetDeltaTime() };

	angle_ += DirectX::XM_PI / 10.0f * dt;
	if (angle_ >= DirectX::XM_PI)
	{
		angle_ -= DirectX::XM_PI;
	}

	Vector3 rotation{ Transform().GetRotation() };
	rotation.y = angle_;
	Transform().SetRotation(rotation);

	Vector3 cameraPos{ System().Get<wtgb::Camera>().position_ };

	cameraPos.x += (input.IsKey(KeyCode::D) ? 1.0f : 0.0f + input.IsKey(KeyCode::A) ? -1.0f : 0.0f) * dt * 10.0f;
	cameraPos.y += (input.IsKey(KeyCode::E) ? 1.0f : 0.0f + input.IsKey(KeyCode::Q) ? -1.0f : 0.0f) * dt * 10.0f;
	cameraPos.z += (input.IsKey(KeyCode::W) ? 1.0f : 0.0f + input.IsKey(KeyCode::S) ? -1.0f : 0.0f) * dt * 10.0f;

	System().Get<wtgb::Camera>().position_ = cameraPos;
}
