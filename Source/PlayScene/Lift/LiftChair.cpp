#include "pch\pch.h"
#include "LiftChair.h"
#include "../LiftStructure.h"


LiftChair::LiftChair(const EntityId _structure, const float _beginLength, const float _maxLength) :
GameObject
{
	"LiftChair.json"
},
	structure_{ _structure },
	length_{ _beginLength },
	lengthMax_{ _maxLength },
	moveSpeedPerSec_{}
{
}

LiftChair::~LiftChair()
{
}

void LiftChair::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());
}

void LiftChair::Update()
{
	const float dt{ System().Get<GameTime>().GetDeltaTime() };

	LiftStructure* pStructure{ FindGameObject<LiftStructure>(structure_) };
	auto [position, rotate]{ pStructure->GetChairPositionAndRotateY(length_) };
	Transform().SetPosition(position);
	Transform().SetRotation(Vector3::Up() * rotate);

	length_ += dt * moveSpeedPerSec_;
	length_ = std::fmodf(length_, lengthMax_);
}

void LiftChair::Release()
{
}

void LiftChair::OnLoadParam(const json& _json)
{
	moveSpeedPerSec_ = _json.value("moveSpeedPerSec", 100.0f);
}
