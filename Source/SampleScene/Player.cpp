#include "pch\pch.h"
#include "Player.h"

#include "GameComponent/GameObjectProperty.h"
//#include "GameComponent/Transform.h"

using namespace wtgb;

Player::Player() : GameObject
{
	[this](GameObjectBuilder& _builder) -> void
	{
		_builder.AddComponent<GameObjectProperty>()
			.BeginSetter()
				.Name("Player")
			.EndSetter()
		/*.AddComponent<Transform>()
			.BeginSetter()
			.EndSetter()*/
		;
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
