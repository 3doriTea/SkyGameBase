#include "pch\pch.h"
#include "WTGBAssert.h"
#include "GameTime.h"
#include "CPRigidBody.h"
#include "CPGameObject.h"
#include "CPTransform.h"
#include "CPCollider.h"
#include "CPRigidBody/PhysicsUtil.h"

namespace
{
	// TODO: ソースとリソースを分ける → jsonで管理する
	const wtgb::PhysicsConfig PHYSICS_CONFIG_DEFAULT
	{
		//.gravity = 9.8f,  // 重力加速度
		.gravity = 13.0f,  // 重力加速度
		.gravityDirection = wtgb::Vector3::Down(),  // 重力の向き
	};
}

wtgb::CPRigidBody::CPRigidBody() :
	physicsConfig_{ PHYSICS_CONFIG_DEFAULT }
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
	using namespace DirectX;

	CPTransform& cpTransform{ System().Get<CPTransform>() };
	CPGameObject& cpGameObject{ System().Get<CPGameObject>() };
	CPCollider& cpCollider{ System().Get<CPCollider>() };
	// delta time
	const float DT{ System().Get<GameTime>().GetDeltaTime() };
	//LOGFLN("__update rb__");

	ForEach([this, &cpTransform, &cpGameObject, &cpCollider, DT](RigidBody& _rb, const size_t _index) -> BreakToken
		{
			_rb.ClearHitCollider();
			float prevT{ FLT_MAX };

			EntityId entityId{ cpGameObject.GetEntityId(_index) };

			Transform* pTransform{ cpTransform.Get(entityId) };

			wassert(pTransform && "Transform取得に失敗");
			if (pTransform == nullptr)
			{
				return {};
			}

			// 重力の適用
			if (_rb.useGravity_)
			{
				// MEMO: v = v + GDir * G * dt
				_rb.velocity_ = _rb.velocity_ 
					+ (physicsConfig_.gravityDirection * (physicsConfig_.gravity * DT));
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
				return {};
			}

			// 当たり判定
			ColliderSet selfSet{ .pCollider = pCollider, .pTransform = pTransform, .pRigidBody = &_rb };
			switch (pCollider->GetColliderType())
			{
			case Collider::Type::Section:
				break;
			case Collider::Type::Sphere:
				cpCollider.ForEach([&_rb, &prevT, &cpGameObject, &cpTransform, &selfSet, _index](Collider& _otherCollider, const size_t _otherIndex) ->BreakToken
					{
						if (_index == _otherIndex)
						{
							return {};  // 自分自身のと衝突を排除
						}

						EntityId otherEntityId{ cpGameObject.GetEntityId(_otherIndex) };

						Transform* pOtherTransform{ cpTransform.Get(otherEntityId) };
						wassert(pOtherTransform && "コライダー付きの相手にTransformがついていなかったよ");

						ColliderSet otherSet{ .pCollider = &_otherCollider, .pTransform = pOtherTransform };

						CollisionInfo collisionInfo{};
						if (PhysicsUtil::IsHitFromSphere(&selfSet, &otherSet, &collisionInfo))
						{
							_rb.AddHitCollider(otherSet.pCollider);

							float velocityX{ _rb.velocity_.x };
							_rb.velocity_ = collisionInfo.reflectionVelocity;
							_rb.velocity_.x = velocityX;
							_rb.push_ = collisionInfo.push;
						}

						return {};
					});
				break;
			default:
				break;
			}

			//if (collisionInfo.depth > FLT_EPSILON)
			{
				Vector3 position{ selfSet.pTransform->GetPosition() };
				_rb.prevPosition_ = position;
				position = position + _rb.push_;
				_rb.push_ = Vector3::Zero();
				selfSet.pTransform->SetPosition(position);
			}

			return {};
		});
}
