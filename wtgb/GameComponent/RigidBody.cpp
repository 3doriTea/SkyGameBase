#include "pch/pch.h"
#include "RigidBody.h"
#include "Collider.h"
#include "WTGBAssert.h"

wtgb::RigidBody::RigidBody() :
	mass_{ 1.0f },
	velocity_{ Vector3::Zero() },
	drag_{ 1.0f },
	angularVelocity_{ Vector3::Zero() },
	angularDrag_{ 1.0f },
	bounciness_{ 1.0f },
	useGravity_{ false },
	onHitCollidersCount_{ 0 },
	onHitColliders_{},
	prevPosition_{ Vector3::Zero() }
{

}

void wtgb::RigidBody::AddHitCollider(Collider* _pCollider)
{
	if (onHitCollidersCount_ >= HIT_COLLIDER_BUFFER_SIZE)
	{
		wassert(false && "コライダに当たりすぎてバッファが足りない");
		return;
	}
	onHitColliders_.at(onHitCollidersCount_) = _pCollider;
	onHitCollidersCount_++;
}

void wtgb::RigidBody::ClearHitCollider()
{
	for (int i = 0; i < onHitCollidersCount_; i++)
	{
		onHitColliders_[i] = nullptr;
	}
	onHitCollidersCount_ = 0;
}

void wtgb::RigidBody::GetHitColliders(std::vector<Collider*>* _pHitColliderVector)
{
	_pHitColliderVector->clear();
	for (auto& hitCollider : onHitColliders_)
	{
		_pHitColliderVector->push_back(hitCollider);
	}
}
