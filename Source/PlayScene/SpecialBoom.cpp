#include "pch\pch.h"
#include "SpecialBoom.h"
#include "StageObjectManager.h"

namespace
{
	const float GET_DISTANCE{ 3.0f };
}

SpecialBoom::SpecialBoom(const Vector3& _position, const EntityId _stageObjManager, const EntityId _player) : GameObject
{
	[&_position](GameObjectBuilder& _builder)
	{
		_builder
			.AddComponent<GameObjectProperty>()
				.BeginSetter()
					.name("SpecialBall")
				.EndSetter()
			.AddComponent<wtgb::Transform>()
				.BeginSetter()
					.position(_position)
				.EndSetter()
			.AddComponent<ModelMesh>()
				.BeginSetter()
					.fileName("Models/Sphere/Sphere.fbx")
				.EndSetter()
			.AddComponent<MeshRenderer>()
				.BeginSetter()
					.shader("Shader/SpecialBall.hlsl")
				.EndSetter()
		.Build();
	}
},
	stageObjManager_{ _stageObjManager },
	player_{ _player }
{
}

SpecialBoom::~SpecialBoom()
{
}

void SpecialBoom::Init()
{
}

void SpecialBoom::Update()
{
	using namespace DirectX;

	GameObject* pPlayerObj{ FindGameObject(player_) };
	wassert(pPlayerObj && "ƒvƒŒƒCƒ„[‚ªŒ©‚Â‚©‚ç‚È‚©‚Á‚½");

	Vector3 playerPos{ pPlayerObj->Transform().GetPosition() };
	Vector3 selfPos{ Transform().GetPosition() };


	Vector3 diff{ playerPos - selfPos };
	float distance{ XMVectorGetX(XMVector3Length(diff)) };
	if (distance < GET_DISTANCE)
	{
		GameObject* pFoundGameObject{ FindGameObject(stageObjManager_) };
		StageObjectManager* pStageObjectManager{ dynamic_cast<StageObjectManager*>(pFoundGameObject) };

		pStageObjectManager->Fire();

		DestroyMe();
	}
}

void SpecialBoom::Release()
{
}
