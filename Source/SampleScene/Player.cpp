#include "pch\pch.h"
#include "Player.h"

Player::Player() : GameObject
{
	[this](GameObjectBuilder& _builder) -> void
	{
		_builder
		.AddComponent<GameObjectProperty>()
			.BeginSetter()
				.Name("Player")
			.EndSetter()
		.AddComponent<wtgb::Transform>()
			.BeginSetter()
				.Position({ 0, 2, 4 })
				.Rotation({ 0, 0, 0 })
				.Scale({ 1, 1, 1 })
			.EndSetter()
		.AddComponent<ModelMesh>()
			.BeginSetter()
				.Model("Models/Oden.fbx")
			.EndSetter()
		.AddComponent<MeshRenderer>()
			.BeginSetter()
				.Shader("Shader/Simple3D.hlsl")
				.Texture("Models/Oden.jpg")
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
}

void Player::Update()
{
}
