#include "pch\pch.h"
#include "CharaEgg.h"

#pragma region ling
CharaEggRing::CharaEggRing(const EntityId _charaEgg, const Vector3& _position, const Vector3& _angles) : GameObject
{
	[_charaEgg , &_position, &_angles](GameObjectBuilder& _builder)
	{
		_builder
			.AddComponent<GameObjectProperty>()
				.BeginSetter()
					.parent(_charaEgg)
					.name("CharaEgg")
				.EndSetter()
			.AddComponent<wtgb::Transform>()
				.BeginSetter()
					.position(_position)
					.rotation(_angles)
					.scale(Vector3::One() * 10.0f)
				.EndSetter()
			.AddComponent<ModelMesh>()
				.BeginSetter()
					.fileName("Models/Ring/Ring.fbx")
				.EndSetter()
			.AddComponent<MeshRenderer>()
				.BeginSetter()
					.shader("Shader/CharaEgg.hlsl")
				.EndSetter()
		.Build();
	}
}
{
}

CharaEggRing::~CharaEggRing()
{
}

void CharaEggRing::Init()
{
}

void CharaEggRing::Update()
{
}
#pragma endregion

CharaEgg::CharaEgg(const Vector3& _position, const EntityId _stageObjManager, const EntityId _player) : GameObject
{
	[&_position](GameObjectBuilder& _builder)
	{
		_builder
			.AddComponent<GameObjectProperty>()
				.BeginSetter()
					.name("CharaEgg")
				.EndSetter()
			.AddComponent<wtgb::Transform>()
				.BeginSetter()
					.position(_position)
					.scale(Vector3::One() * 10.0f)
				.EndSetter()
			.AddComponent<ModelMesh>()
				.BeginSetter()
					.fileName("Models/Neko/NekoSphereV2.fbx")
				.EndSetter()
			.AddComponent<MeshRenderer>()
				.BeginSetter()
					.shader("Shader/Simple3D.hlsl")
					.texture("Models/Neko/TextureSphereNeko.png")
				.EndSetter()
		.Build();
	}
},
stageObjManager_{ _stageObjManager },
player_{ _player }
{
}

CharaEgg::~CharaEgg()
{
}

void CharaEgg::Init()
{
}

void CharaEgg::Update()
{
}

