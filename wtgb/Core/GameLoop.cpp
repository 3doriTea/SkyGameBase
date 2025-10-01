#include "pch\pch.h"
#include "GameLoop.h"
#include "IGame.h"

wtgb::GameLoop::GameLoop() :
	isRunning_{ false },
	deltaTime_{ 0.0f }
{
}

wtgb::GameLoop::~GameLoop()
{
}

void wtgb::GameLoop::RunLoop(GameSystemCollection* _pGameSystemRegister)
{
	isRunning_ = true;

	while (isRunning_)
	{
		_pGameSystemRegister->UpdateCycle();
	}
}

void wtgb::GameLoop::Stop()
{
	isRunning_ = false;
}
