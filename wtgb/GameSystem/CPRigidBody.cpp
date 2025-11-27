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
		.gravity = 9.8f,  // 重力加速度
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

	ForEach([this, &cpTransform, &cpGameObject, &cpCollider, DT](RigidBody& _rb, const size_t _index)
		{
			_rb.ClearHitCollider();

			EntityId entityId{ cpGameObject.GetEntityId(_index) };

			Transform* pTransform{ cpTransform.Get(entityId) };

			wassert(pTransform && "Transform取得に失敗");
			if (pTransform == nullptr)
			{
				return;
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
				return;
			}

			// 当たり判定
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

						CollisionInfo collisionInfo{};
						if (PhysicsUtil::IsHitFromSphere(&selfSet, &otherSet, &collisionInfo))
						{
							// 当たったコライダーとして追加
							_rb.AddHitCollider(otherSet.pCollider);

							// 壁の法線
							const Vector3 N{ XMVector3Normalize(collisionInfo.normal) };
							// 反発係数
							const float E{ std::clamp(_rb.bounciness_, 0.0f, 1.0f) };
							// 進入速度
							const Vector3 V{ _rb.velocity_ };

							// TODO: 回転を入れた反射をさせる

							// 壁刷りベクトル
							//Vector3 r{ V - 2.0f * XMVectorGetX(XMVector3Dot(V, N)) * N };

							// 反射ベクトル
							// REF: http://marupeke296.com/COL_Basic_No5_WallVector.html
							// MEMO: r = v + 2 * a * n(normal)
							Vector3 r{ V + 2.0f * E * N };

							_rb.velocity_ = r;

							//const float K{ (1.0f + E) * XMVectorGetX(XMVector3Dot(V, N)) };

							//Vector3 position{ selfSet.pTransform->GetPositionWorld() };

							if (collisionInfo.depth > 3.0f)
							{
								Vector3 position{ selfSet.pTransform->GetPosition()};
								position = position + N * collisionInfo.depth;
								selfSet.pTransform->SetPosition(position);
							}

							//_rb.velocity_ = V - N * K;*/
						}
					});
				break;
			default:
				break;
			}
		});
}
