#include "pch\pch.h"
#include "Game.h"
#include "IGame.h"
#include "GameLoop.h"
#include "GameSystemCollection.h"

std::u8string_view wtgb::Game::Title()
{
	if (pGame_)
	{
		return pGame_->GetTitle();
	}
	return u8"ゲーム";
}

std::u8string_view wtgb::Game::Version()
{
	if (pGame_)
	{
		return pGame_->GetVersion();
	}
	return u8"1.2.1";
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
	// システムのまとめて動かすやつ
	GameSystemCollection gameSystemCollection{};
	GameSystemCollection::GameSystemAdder adder{ &gameSystemCollection };

	// システムの登録をしてもらう
	pGame_->StartRegister(adder);

	// 登録したシステムの初期化処理
	gameSystemCollection.Init();

	// ゲームループを作る
	GameLoop gameLoop{};  // stackに作る
	pGameLoop_ = &gameLoop;

	// ゲームループを実行！
	pGameLoop_->RunLoop(&gameSystemCollection);

	// ゲームループが終了した
	pGameLoop_ = nullptr;

	// ゲームループが終わったらシステムの終了処理
	gameSystemCollection.End();
}

wtgb::IGame* wtgb::Game::pGame_{ nullptr };
wtgb::GameLoop* wtgb::Game::pGameLoop_{ nullptr };
