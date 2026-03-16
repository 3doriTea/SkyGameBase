#include "Cloud.h"

Cloud::Cloud(const EntityId _parentLift) :
	GameObject{ "Play/LiftChilds/Cloud.json" }
{
	// 指定のリフト座席に固定される
	Property().SetParent(_parentLift);
}

Cloud::~Cloud()
{
}

void Cloud::Init()
{
}

void Cloud::Update()
{
	// TODO: 簡易的に座標設定
	Transform().SetPosition(Mathf::Lerp(randomBegin_, randomEnd_, 0.5f));
}

void Cloud::Release()
{
}

void Cloud::OnLoad(const json& _json)
{
	randomBegin_ = SafeGet<Vector3>(_json, "randomBegin");
	randomEnd_ = SafeGet<Vector3>(_json, "randomEnd");
}
