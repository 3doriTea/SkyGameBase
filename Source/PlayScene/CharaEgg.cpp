#include "pch\pch.h"
#include "CharaEgg.h"
#include "PlayScene.h"
#include "StageObjectManager.h"

#pragma region ling
CharaEggRing::CharaEggRing(const EntityId _charaEgg, const Vector3& _angles) :
	GameObject{ "StageObj/CharaEggRing.json" }
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

CharaEgg::CharaEgg(const Vector3& _position, const EntityId _stageObjManager, const EntityId _player) :
	GameObject{ "CharaEgg.json" },
	stageObjManager_{ _stageObjManager },
	player_{ _player }
{
	Transform().SetPosition(_position);
}

CharaEgg::~CharaEgg()
{
}

void CharaEgg::OnLoadParam(const json& _json)
{
	using DirectX::XM_PI;

	float rotSpeedPiDivPerSec{ _json["rotSpeedDivPiPerSec"].get<float>() };
	rotAngleSpeedPerSec_ = XM_PI / rotSpeedPiDivPerSec;

	ringsAngles_.clear();
	for (const auto& ring : _json["rings"])
	{
		ringsAngles_.push_back(ring["angles"].get<Vector3>());
	}
}

void CharaEgg::Init()
{
	using DirectX::XM_PI;
	using DirectX::XM_PIDIV2;

	OnLoadParam(GetComponent<Parameter>().Load());

	PlayScene* pPlayScene{ GetScene<PlayScene>() };
	wassert(pPlayScene && "プレイシーン取得に失敗");
	if (pPlayScene == nullptr)
	{
		return;  // プレイシーン取得に失敗したため何もできない
	}

	for (int i = 0; i < ringsAngles_.size(); i++)
	{
		EntityId ring
		{
			pPlayScene->Instantiate<CharaEggRing>(
				GetEntityId(),
				ringsAngles_[i])
		};
		rings_.push_back(ring);
	}
}

void CharaEgg::Update()
{
	using namespace DirectX;

	PlayScene* pPlayScene{ GetScene<PlayScene>() };
	if (pPlayScene == nullptr)
	{
		return;  // プレイシーンが取得できないなら何もしない
	}
	
	const float dt{ System().Get<GameTime>().GetDeltaTime() };

	Vector3 rotation{ Transform().GetRotation() };
	float rotAngle{ rotAngleSpeedPerSec_ * dt };
	rotation.y += rotAngle;
	Transform().SetRotation(rotation);

	WorldConfig worldConfig{ pPlayScene->GetWorldConfig() };

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
		for (const auto& ringEntity : rings_)
		{
			FindGameObject(ringEntity)->DestroyMe();
		}

		DestroyMe();
	}
}

void CharaEgg::Release()
{
}
