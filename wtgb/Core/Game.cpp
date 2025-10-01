#include "pch\pch.h"
#include "Game.h"
#include "IGame.h"
#include "GameLoop.h"
#include "GameSystemCollection.h"

std::string wtgb::Game::Title()
{
	if (pGame_)
	{
		return pGame_->GetTitle();
	}
	return "";
}

std::string wtgb::Game::Version()
{
	if (pGame_)
	{
		return pGame_->GetVersion();
	}
	return "";
}

void wtgb::Game::Exit()
{
	if (pGameLoop_)
	{
		pGameLoop_->Stop();
	}
}

void wtgb::Game::RunProcess()
{
	GameSystemCollection* pGameSystemRegister{ new GameSystemCollection{} };

	pGame_->Start(pGameSystemRegister);

	pGameLoop_ = new GameLoop{};

	pGameLoop_->RunLoop(pGameSystemRegister);

	SAFE_DELETE(pGameLoop_);

	SAFE_DELETE(pGameSystemRegister);
}

wtgb::IGame* wtgb::Game::pGame_{ nullptr };
wtgb::GameLoop* wtgb::Game::pGameLoop_{ nullptr };
