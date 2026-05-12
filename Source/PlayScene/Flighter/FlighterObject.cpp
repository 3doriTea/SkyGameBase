#include "FlighterObject.h"

FlighterObject::FlighterObject(
	const EntityId _flighterController,
	const EntityId _player,
	const EntityId _targetChair,
	const FlighterFlag _flag,
	const ModelHandle _hModel) :
	GameObject{ "FlighterObject.json" },
	flighterController_{ _flighterController },
	targetChair_{ _targetChair },
	player_{ _player },
	hModel_{ _hModel },
	flag_{ _flag },
	isRangeOut_{ false },
	moveRatioPerSec_{}
{
}

void FlighterObject::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());

	GetComponent<ModelMesh>().SetModel(hModel_);
}

void FlighterObject::Update()
{
	const float DT{ System().Get<GameTime>().GetDeltaTime() };

	GameObject* pPlayerObj{ FindGameObject(player_) };
	wassert(pPlayerObj && "プレイヤーオブジェクトが見つからなかった");
	GameObject* pTargetChair{ FindGameObject(targetChair_) };
	wassert(pTargetChair && "ターゲット椅子オブジェクトが見つからなかった");

	if (!pPlayerObj || !pTargetChair)
	{
		return;  // 片方でも見つからなければ何もできない
	}

	Vector3 playerPosition{ pPlayerObj->Transform().GetPosition() };
	Vector3 targetChairPosition{ pTargetChair->Transform().GetPosition() };

	// 各軸でのオフセットを登録
	Vector3 position
	{
		playerPosition.x + toMargine_.playerX,
		targetChairPosition.y + toMargine_.chairY,
		targetChairPosition.z + toMargine_.chairZ,
	};
	Transform().SetPosition(position);
}

void FlighterObject::Release()
{
}

void FlighterObject::ReFollow(
	const EntityId _targetChair,
	const float _toPlayerX,
	const float _toChairY,
	const float _toChairZ)
{
	// ターゲット登録
	targetChair_ = _targetChair;
	// オフセットを登録
	toMargine_.playerX = _toPlayerX;
	toMargine_.chairY = _toChairY;
	toMargine_.chairZ = _toChairZ;

	LOGFLN(
		"toMargine_[]: ({}, {}, {})",
		toMargine_.playerX,
		toMargine_.chairY,
		toMargine_.chairZ);

	GameObject* pPlayerObj{ FindGameObject(player_) };
	wassert(pPlayerObj && "プレイヤーオブジェクトが見つからなかった");
	GameObject* pTargetChair{ FindGameObject(targetChair_) };
	wassert(pTargetChair && "ターゲット椅子オブジェクトが見つからなかった");

	if (!pPlayerObj || !pTargetChair)
	{
		return;  // 片方でも見つからなければ何もできない
	}

	// 範囲外も解消
	isRangeOut_ = false;
}

void FlighterObject::OnLoadParam(const json& _json)
{
	moveRatioPerSec_ = _json.value("moveRatioPerSec", 10.0f);
}
