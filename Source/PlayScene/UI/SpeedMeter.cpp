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
	GetScene<PlayScene>().Instantiate<NumberPlate>();
}

void SpeedMeter::Update()
{
}

void SpeedMeter::Release()
{
}
