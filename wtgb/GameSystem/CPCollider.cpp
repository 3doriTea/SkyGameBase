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
	IMeshSimple* pDebugSphere{ System().Get<Debug>().GetDebugSphere() };
	ShaderHandle hDebugShader{ System().Get<Debug>().GetDebugShader() };

	ForEach([&cpGameObject, &cpTransform, &cpMeshRenderer, pDebugSphere, hDebugShader](const Collider& _collider, const size_t _index)
		{
			EntityId entityId{ cpGameObject.GetEntityId(_index) };

			Transform* pTransform{ cpTransform.Get(entityId) };

			wassert(pTransform && "Transform‚ª‚È‚©‚Á‚½");
			if (pTransform == nullptr)
			{
				return;
			}

			switch (_collider.colliderType_)
			{
			case Collider::Type::Section:
				break;
			case Collider::Type::Sphere:
				cpMeshRenderer.Render(pDebugSphere, pTransform, hDebugShader);
				break;
			default:
				break;
			}

		});
}
