#include "pch\pch.h"
#include "WTGBAssert.h"
#include "GameTime.h"
#include "CPRigidBody.h"
#include "CPGameObject.h"
#include "CPTransform.h"
#include "CPCollider.h"
#include "CPRigidBody/PhysicsUtil.h"

wtgb::CPRigidBody::CPRigidBody()
{
}

wtgb::CPRigidBody::~CPRigidBody()
{
}

void wtgb::CPRigidBody::Init()
{
}

void wtgb::CPRigidBody::Update()
{
	CPTransform& cpTransform{ System().Get<CPTransform>() };
	CPGameObject& cpGameObject{ System().Get<CPGameObject>() };
	CPCollider& cpCollider{ System().Get<CPCollider>() };
	// delta time
	const float DT{ System().Get<GameTime>().GetDeltaTime() };

	ForEach([&cpTransform, &cpGameObject, &cpCollider, DT](RigidBody& _rb, const size_t _index)
		{
			_rb.ClearHitCollider();

			EntityId entityId{ cpGameObject.GetEntityId(_index) };

			Transform* pTransform{ cpTransform.Get(entityId) };

			wassert(pTransform && "Transform取得に失敗");
			if (pTransform == nullptr)
			{
				return;
			}

			// 剛体速度の適用
			Vector3 position{ pTransform->GetPositionWorld() };
			position = position + _rb.velocity_ * DT;
			pTransform->SetPositionWorld(position);
			_rb.velocity_ = _rb.velocity_ * _rb.drag_;

			// ラジアンオイラー回転角速度の適用
			Vector3 rotation{ pTransform->GetRotationWorld() };
			rotation = rotation + _rb.angularVelocity_ * DT;
			pTransform->SetRotationWorld(rotation);
			_rb.angularVelocity_ = _rb.angularVelocity_ * _rb.drag_;

			Collider* pCollider{ cpCollider.Get(entityId) };
			wassert(pCollider && "コライダついてないよー");
			if (pCollider == nullptr)
			{
				// コライダーがついていないなら無視
				return;
			}

			ColliderSet selfSet{ .pCollider = pCollider, .pTransform = pTransform };

			switch (pCollider->GetColliderType())
			{
			case Collider::Type::Section:
				break;
			case Collider::Type::Sphere:
				cpCollider.ForEach([&_rb, &cpGameObject, &cpTransform, &selfSet, _index](Collider& _otherCollider, const size_t _otherIndex)
					{
						if (_index == _otherIndex)
						{
							return;  // 自分自身のと衝突を排除
						}

						EntityId otherEntityId{ cpGameObject.GetEntityId(_otherIndex) };

						Transform* pOtherTransform{ cpTransform.Get(otherEntityId) };
						wassert(pOtherTransform && "コライダー付きの相手にTransformがついていなかったよ");

						ColliderSet otherSet{ .pCollider = &_otherCollider, .pTransform = pOtherTransform };

						if (PhysicsUtil::IsHitFromSphere(&selfSet, &otherSet))
						{
							_rb.AddHitCollider(otherSet.pCollider);
						}
					});
				break;
			default:
				break;
			}
		});
}
