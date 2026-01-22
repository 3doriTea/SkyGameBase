#include "SpeedController.h"

SpeedController::SpeedController(const EntityId _player) :
	GameObject{ "Simple.json" }
{
}

SpeedController::~SpeedController()
{
}

void SpeedController::Init()
{
}

void SpeedController::Update()
{
}

void SpeedController::Release()
{
}

float SpeedController::GetGreyOutRatio() const
{
	if (currentSpeedValue_ < speedHighMin_)
	{
		return 0.0f;
	}

	if (currentSpeedValue_ >= speedGLOCLine_)
	{
		return 1.0f;
	}

	(currentSpeedValue_ - speedHighMin_) / (speedHighMin_)
}

bool SpeedController::IsGLOC() const
{
	return currentSpeedValue_ >= speedGLOCLine_;
}

SpeedType SpeedController::GetSpeedType() const
{
	if (currentSpeedValue_ <= speedStopMin_)
	{
		return SpeedType::Stop;  // Ž~‚Ü‚Á‚Ä‚¢‚é”»’è
	}
	else if (currentSpeedValue_ < speedGoodMin_)
	{
		return SpeedType::TooSlow;  // —Ç‚­‚È‚¢’x‚¢‘¬“x
	}
	else if (currentSpeedValue_ < speedHighMin_)
	{
		return SpeedType::Good;  // ‘¬‚·‚¬‚È‚¢—Ç‚¢‘¬“x
	}
	else  // ‘¬‚·‚¬‚é
	{
		return SpeedType::Excissive;
	}
}
