#include "pch\pch.h"
#include "WTGBAssert.h"
#include "GameTime.h"
#include "CPRigidBody.h"
#include "CPGameObject.h"
#include "CPTransform.h"

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
	// delta time
	const float DT{ System().Get<GameTime>().GetDeltaTime() };

	ForEach([&cpTransform, &cpGameObject, DT](RigidBody& _rb, const size_t _index)
		{
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
		});
}
