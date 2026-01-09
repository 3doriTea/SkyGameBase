#include "pch\pch.h"
#include "PresentSphere.h"
#include "Common.h"
#include "Components/ItemAnim.h"
#include "Systems/CPItemAnim.h"

namespace
{
	static const float BOUNDING_TIME{ 2.0f };
	static const float ANIM_TIME{ 3.0f };
	static const float BOUNDED_RATIO{ 5.0f / 100.0f };  // バウンドした後のレート
}

PresentSphere::PresentSphere(const EntityId _player, const Vector3& _position, const Vector3& _dropPosition) :
	GameObject{ "StageObj/PresentSphere.json" },
	player_{ _player },
	isHitted_{ false },
	isBounded_{ false },
	isBoundedOnce_{ false }
{
	Transform().SetPosition(_position);
	GetComponent<Collider>().SetTagFlag(CT_PLAYER);
	ItemAnim& itemAnim{ AddComponent<ItemAnim>() };
	itemAnim.SetStartPos(_position);
	itemAnim.SetEndPos(_dropPosition);
	itemAnim.SetTotalTime(ANIM_TIME);
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
	ItemAnim& itemAnim{ GetComponent<ItemAnim>() };
	
	if (isHitted_)
	{
		return;  // 既にとっている
	}

	if (itemAnim.IsFinished())  // アニメーション終わって取得可能状態
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

	if (isBounded_ == false
		&& itemAnim.GetRatio() > BOUNDED_RATIO)
	{
		isBounded_ = true;
		isBoundedOnce_ = true;
	}

	// TODO: 不要
	//if (isBounding_)
	//{
	//	timeLeft_ -= dt;
	//	if (timeLeft_ <= 0.0f)
	//	{
	//		rb.SetUseGravity(false);
	//		rb.SetVelocity(Vector3::Zero());
	//		isStopping_ = true;  // その場で止まる！
	//	}
	//	return;
	//}

	// TODO: 不要
	/*std::vector<Collider*> pColliders{};
	rb.GetHitColliders(&pColliders);
	for (Collider* pCollider : pColliders)
	{
		if (pCollider && pCollider->GetColliderType() == Collider::Type::Section)
		{
			isBounded_ = true;
			isBounding_ = true;
			return;
		}
	}*/
}

void PresentSphere::Release()
{
}

bool PresentSphere::CheckOnBounded()
{
	if (isBoundedOnce_)
	{
		isBoundedOnce_ = false;
		return true;
	}
	return false;
}
