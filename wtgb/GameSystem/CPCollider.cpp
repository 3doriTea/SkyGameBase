#include "pch/pch.h"
#include "WTGBAssert.h"
#include "CPCollider.h"
#include "CPGameObject.h"
#include "CPTransform.h"
#include "CPMeshRenderer.h"

#include "GameSystem/ModelMesh/IMeshSimple.h"
#include "GameSystem/Debug.h"
#include "GameSystem/Model.h"

void wtgb::CPCollider::Update()
{
	CPGameObject& cpGameObject{ System().Get<CPGameObject>() };
	CPTransform& cpTransform{ System().Get<CPTransform>() };
	CPMeshRenderer& cpMeshRenderer{ System().Get<CPMeshRenderer>() };

	ForEach([&cpGameObject, &cpTransform, &cpMeshRenderer](const Collider& _collider, const size_t _index) -> BreakToken
		{
			EntityId entityId{ cpGameObject.GetEntityId(_index) };

			Transform* pTransform{ cpTransform.Get(entityId) };

			wassert(pTransform && "Transformがなかった");
			if (pTransform == nullptr)
			{
				return {};
			}

			switch (_collider.colliderType_)
			{
			case Collider::Type::Section:
				break;
			case Collider::Type::Sphere:
				break;
			default:
				break;
			}

			return {};
		});
}
