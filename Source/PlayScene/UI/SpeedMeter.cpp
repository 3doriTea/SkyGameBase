#include "SpeedMeter.h"
#include "../PlayScene.h"
#include "UI/NumberPlate.h"


SpeedMeter::SpeedMeter(const EntityId _player) :
	GameObject{ "Simple.json" }
{
}

SpeedMeter::~SpeedMeter()
{
}

void SpeedMeter::Init()
{
	numberPlate_ = GetScene<PlayScene>().Instantiate<NumberPlate>();
	NumberPlate* pNumberPlate{ dynamic_cast<NumberPlate*>(FindGameObject(numberPlate_)) };

	pNumberPlate->SetPosition();
}

void SpeedMeter::Update()
{
}

void SpeedMeter::Release()
{
}
