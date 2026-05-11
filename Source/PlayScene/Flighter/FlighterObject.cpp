#include "FlighterObject.h"

FlighterObject::FlighterObject(
	const EntityId _flighterController,
	const EntityId _targetChair,
	const EntityId _player,
	const FlighterFlag _flag,
	const ModelHandle _hModel) :
	GameObject{ "FlighterObject.json" },
	flighterController_{ _flighterController },
	targetChair_{ _targetChair },
	player_{ _player },
	hModel_{ _hModel },
	flag_{ _flag },
	isRangeOut_{}
{
}

void FlighterObject::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());

	GetComponent<ModelMesh>().SetModel(hModel_);
}

void FlighterObject::Update()
{
	GameObject* pPlayerObj{ FindGameObject(player_) };
	wassert(pPlayerObj && "プレイヤーオブジェクトが見つからなかった");
	GameObject* pTargetChair{ FindGameObject(targetChair_) };
	wassert(pTargetChair && "ターゲット椅子オブジェクトが見つからなかった");

	if (!pPlayerObj || !pTargetChair)
	{
		return;  // 片方でも見つからなければ何もできない
	}

	pPlayerObj->Transform().GetPosition();
}

void FlighterObject::Release()
{
}

void FlighterObject::OnLoadParam(const json& _json)
{
}
