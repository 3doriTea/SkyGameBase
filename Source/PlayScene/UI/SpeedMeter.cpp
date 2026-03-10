#include "SpeedMeter.h"
#include "../PlayScene.h"
#include "UI/NumberPlate.h"
#include "../Player.h"


SpeedMeter::SpeedMeter(const EntityId _player) :
	GameObject{ "Play/UI/SpeedMeter.json" }
{
}

SpeedMeter::~SpeedMeter()
{
}

void SpeedMeter::OnLoadParam(const json& _json)
{
	baseCanvasSize_ = SafeGet<Vector2Int>(_json, "baseCanvasSize");
	numbersCenterOffset_ = SafeGet<int>(_json, "numbersCenterOffset");
	numbersImageFile_ = SafeGet<std::string>(_json, "numbersImageFile");
}

void SpeedMeter::Init()
{
	PlayScene* pPlayScene{ GetScene<PlayScene>() };
	wassert(pPlayScene && "プレイシーンの取得に失敗");
	if (pPlayScene == nullptr)
	{
		return;  // プレイシーンの取得に失敗すると何もできない
	}

	numberPlate_ = pPlayScene->Instantiate<NumberPlate>(numbersImageFile_);
	NumberPlate* pNumberPlate{ dynamic_cast<NumberPlate*>(FindGameObject(numberPlate_)) };
	pNumberPlate->SetBaseCanvasSize(baseCanvasSize_);
	pNumberPlate->SetPosition({ baseCanvasSize_.x / 2 + numbersCenterOffset_, 0 });
}

void SpeedMeter::Update()
{
	Player* pPlayer{ dynamic_cast<Player*>(FindGameObject(player_)) };
	wassert(pPlayer && "プレイヤーが見つからない");
	
	NumberPlate* pNumberPlate{ dynamic_cast<NumberPlate*>(FindGameObject(numberPlate_)) };
	wassert(pNumberPlate && "ナンバープレートが見つからない");


	if (pPlayer && pNumberPlate)
	{
		Vector3 velocity{ pPlayer->GetComponent<RigidBody>().GetVelocity() };
		pNumberPlate->SetNumber(static_cast<uint32_t>(velocity.z));
	}
}

void SpeedMeter::Release()
{
}

