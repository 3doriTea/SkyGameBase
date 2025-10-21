#include "pch\pch.h"
#include "Game.h"
#include "IGame.h"
#include "GameLoop.h"
#include "GameSystemCollection.h"

std::string_view wtgb::Game::Title()
{
	if (pGame_)
	{
		return pGame_->GetTitle();
	}
	return "No name game DX11";
}

std::string_view wtgb::Game::Version()
{
	if (pGame_)
	{
		return pGame_->GetVersion();
	}
	return "0.0.1";
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

	// “o˜^‚ð‚µ‚Ä‚à‚ç‚¤
	pGame_->StartRegister(GameSystemCollection::GameSystemAdder{ pGameSystemRegister });

	// ‰Šú‰»ˆ—
	pGameSystemRegister->Init();

	// Ý’è‚ð‚µ‚Ä‚à‚ç‚¤
	pGame_->StartSetup(GameSystemCollection::GameSystemInitViewer{ pGameSystemRegister });

	pGameLoop_ = new GameLoop{};

	pGameLoop_->RunLoop(pGameSystemRegister);

	pGameSystemRegister->End();

	SAFE_DELETE(pGameLoop_);

	SAFE_DELETE(pGameSystemRegister);
}

wtgb::IGame* wtgb::Game::pGame_{ nullptr };
wtgb::GameLoop* wtgb::Game::pGameLoop_{ nullptr };
