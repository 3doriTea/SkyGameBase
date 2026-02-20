#include "pch\pch.h"
#include "CharaBall.h"
#include "PlayScene.h"
#include "Player.h"


CharaBall::CharaBall(
	const Vector3& _position,
	const Vector3& _velocity,
	const EntityId _player) :
	GameObject{ "CharaBall.json" },
	player_{ _player }
{
	Transform().SetPosition(_position);
	GetComponent<RigidBody>().SetVelocity(_velocity);
}

CharaBall::~CharaBall()
{
}

void CharaBall::Init()
{
}

void CharaBall::Update()
{
	PlayScene* pPlayScene{ GetScene<PlayScene>() };
	if (pPlayScene == nullptr)
	{
		return;  // プレイシーンが取得できなければ何もしない
	}

	WorldConfig worldConfig{ pPlayScene->GetWorldConfig() };

	Vector3 pos{ Transform().GetPosition() };

	RigidBody& rb{ GetComponent<RigidBody>() };
	Vector3 v{ rb.GetVelocity() };

	GameObject* pPlayerObj{ FindGameObject(player_) };
	Vector3 playerPos{ pPlayerObj->Transform().GetPosition() };

	if (pos.z > playerPos.z)
	{
		v.z -= 10.0f;
	}
	else
	{
		v.z += 10.0f;
	}

	if ((pos.x < worldConfig.safeZoneXMin && v.x < 0)
	|| (pos.x > worldConfig.safeZoneXMax && v.x > 0))
	{
		v.x *= -1.0f;
		rb.SetVelocity(v);
	}
}

void CharaBall::Release()
{
}
