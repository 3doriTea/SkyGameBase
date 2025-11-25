#include "pch/pch.h"
#include "RigidBody.h"
#include "Collider.h"
#include "WTGBAssert.h"

wtgb::RigidBody::RigidBody() :
	velocity_{ Vector3::Zero() },
	drag_{ 1.0f },
	angularVelocity_{ Vector3::Zero() },
	angularDrag_{ 1.0f },
	useSphereCollider_{ false },
	useGravity_{ false }
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
