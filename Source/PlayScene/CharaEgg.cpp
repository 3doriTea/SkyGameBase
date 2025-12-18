#include "pch\pch.h"
#include "CharaEgg.h"
#include "PlayScene.h"
#include "StageObjectManager.h"

#pragma region ling
CharaEggRing::CharaEggRing(const EntityId _charaEgg, const Vector3& _angles) : GameObject
{
	"StageObj/CharaEggRing.json"
}
{
	Property().SetParent(_charaEgg);
	Transform().SetRotation(_angles);
}

CharaEggRing::~CharaEggRing()
{
}

void CharaEggRing::Init()
{
}

void CharaEggRing::Update()
{
	using DirectX::XM_PI;
	const float dt{ System().Get<GameTime>().GetDeltaTime() };

	Vector3 rotation{ Transform().GetRotation() };
	float rotAngle{ XM_PI / 1.0f * dt };
	rotation.x += rotAngle;
	Transform().SetRotation(rotation);
}

void CharaEggRing::Release()
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
					.scale(Vector3::One() * 1.0f)
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
	using DirectX::XM_PI;
	using DirectX::XM_PIDIV2;

	const std::array<Vector3, 3> ANGLES
	{
		Vector3{ 0, 0, 0 },
		Vector3{ 0, XM_PIDIV2, XM_PIDIV2 },
		Vector3{ XM_PIDIV2, 0, 0 },
	};
	for (int i = 0; i < ANGLES.size(); i++)
	{
		EntityId ring
		{
			GetScene<PlayScene>().Instantiate<CharaEggRing>(
				GetEntityId(),
				ANGLES[i])
		};
		rings_.push_back(ring);
	}
}

void CharaEgg::Update()
{
	using namespace DirectX;
	
	const float dt{ System().Get<GameTime>().GetDeltaTime() };

	Vector3 rotation{ Transform().GetRotation() };
	float rotAngle{ XM_PI / 5.0f * dt };
	rotation.y += rotAngle;
	Transform().SetRotation(rotation);

	WorldConfig worldConfig{ GetScene<PlayScene>().GetWorldConfig() };

	GameObject* pPlayerObj{ FindGameObject(player_) };
	wassert(pPlayerObj && "プレイヤーが見つからなかった");

	Vector3 playerPos{ pPlayerObj->Transform().GetPosition() };
	Vector3 selfPos{ Transform().GetPosition() };


	Vector3 diff{ playerPos - selfPos };
	float distance{ XMVectorGetX(XMVector3Length(diff)) };
	if (distance < worldConfig.eggGetDistance)
	{
		GameObject* pFoundGameObject{ FindGameObject(stageObjManager_) };
		StageObjectManager* pStageObjectManager{ dynamic_cast<StageObjectManager*>(pFoundGameObject) };

		pStageObjectManager->Fire();

		// リングも消す
		for (auto ringEntity : rings_)
		{
			FindGameObject(ringEntity)->DestroyMe();
		}

		DestroyMe();
	}
}

void CharaEgg::Release()
{
}
