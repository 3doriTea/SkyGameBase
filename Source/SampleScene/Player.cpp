#include "pch\pch.h"
#include "Player.h"

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
				.position({ 0, 2, 4 })
				.rotation({ 0, 0, 0 })
				.scale({ 1, 1, 1 })
			.EndSetter()
		.AddComponent<ModelMesh>()
			.BeginSetter()
				.fileName("Models/Oden.fbx")
			.EndSetter()
		/*
		.AddComponent<MeshRenderer>()
			.BeginSetter()
				.Shader("Shader/Simple3D.hlsl")
				.Texture("Models/Oden.jpg")
			.EndSetter()*/
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
	GetComponent<ModelMesh>().Load();
}

void Player::Update()
{
}
