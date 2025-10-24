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
