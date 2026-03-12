#include "pch\pch.h"
#include "LiftChair.h"
#include "../LiftStructure.h"

namespace
{
	static const float LINE_MARGIN{ 5.0f };
}

LiftChair::LiftChair(const EntityId _structure, const float _beginLength, const float _maxLength) :
GameObject
{
	[this](GameObjectBuilder& _builder)
	{
		_builder
			.AddComponent<GameObjectProperty>()
				.BeginSetter()
					.name("LiftChair")
				.EndSetter()
			.AddComponent<wtgb::Transform>()
				.BeginSetter()
					//.position({ 0, 10, 50 })
				.EndSetter()
			.AddComponent<ModelMesh>()
				.BeginSetter()
					.fileName("Models/LiftChair/LiftChair.fbx")
				.EndSetter()
			.AddComponent<MeshRenderer>()
				.BeginSetter()
					.shader("Shader/Simple3D.hlsl")
				.EndSetter()
		.Build();
	},
},
	structure_{ _structure },
	length_{ _beginLength },
	lengthMax_{ _maxLength }
{
}

LiftChair::~LiftChair()
{
}

void LiftChair::Init()
{
}

void LiftChair::Update()
{
	const float dt{ System().Get<GameTime>().GetDeltaTime() };

	LiftStructure* pStructure{ FindGameObject<LiftStructure>(structure_) };
	auto [position, rotate]{ pStructure->GetChairPositionAndRotateY(length_) };
	Transform().SetPosition(position);
	Transform().SetRotation(Vector3::Up() * rotate);

	length_ += dt;
}

void LiftChair::Release()
{
}
