#include "pch\pch.h"
#include "PresentSphere.h"

namespace
{
	static const float BOUNDING_TIME{ 2.0f };
}

PresentSphere::PresentSphere(const EntityId _player, const Vector3& _position) :
	GameObject{ "StageObj/PresentSphere.json" },
	isBounding_{ false },
	timeLeft_{ BOUNDING_TIME },
	isStopping_{ false },
	player_{ _player },
	isHitted_{ false },
	isBounded_{ false }
{
	Transform().SetPosition(_position);
}

PresentSphere::~PresentSphere()
{
}

void PresentSphere::Init()
{
}

void PresentSphere::Update()
{
	using namespace DirectX;

	const float dt{ System().Get<GameTime>().GetDeltaTime() };
	RigidBody& rb{ GetComponent<RigidBody>() };
	
	if (isHitted_)
	{
		return;  // 既にとっている
	}

	if (isStopping_)
	{
		GameObject* pPlayerObj{ FindGameObject(player_) };

		// TODO: プレイヤー以外もプレゼントを取れるようにするため、球と球の当たり判定を復活させる
		float toPlayerDistance  // プレイヤーまでの距離
		{
			XMVectorGetX(XMVector3Length(pPlayerObj->Transform().GetPosition() - this->Transform().GetPosition()))
		};

		float threshold  // 当たったとみなすしきい値
		{
			pPlayerObj->Transform().GetScale().x + this->Transform().GetScale().x
		};

		if (toPlayerDistance <= threshold)
		{
			isHitted_ = true;  // 当たったから取られたよ！
		}
		return;
	}

	if (isBounding_)
	{
		timeLeft_ -= dt;
		if (timeLeft_ <= 0.0f)
		{
			rb.SetUseGravity(false);
			rb.SetVelocity(Vector3::Zero());
			isStopping_ = true;  // その場で止まる！
		}
		return;
	}


	std::vector<Collider*> pColliders{};
	rb.GetHitColliders(&pColliders);
	for (Collider* pCollider : pColliders)
	{
		if (pCollider && pCollider->GetColliderType() == Collider::Type::Section)
		{
			isBounded_ = true;
			isBounding_ = true;
			return;
		}
	}
}

void PresentSphere::Release()
{
}

bool PresentSphere::IsBounded()
{
	if (isBounded_)
	{
		// 跳ね返りを取得できたためリセットする
		isBounded_ = false;
		return true;
	}
	else
	{
		return false;
	}
}
