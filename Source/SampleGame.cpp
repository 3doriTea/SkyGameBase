#include "pch\pch.h"
#include "SampleGame.h"

#include "GameSystem/GameTime.h"
#include "GameSystem/Debug.h"
#include "GameSystem/Direct3D.h"

void SampleGame::Start(GameSystemCollection* _pGameSystemRegister)
{
	using namespace wtgb;

	_pGameSystemRegister
		->Register<GameTime>()
		.Register<Debug>()
		.Register<Direct3D>()
	;
}
