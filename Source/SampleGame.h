#pragma once
#include <wtgb.h>

class SampleGame : public IGame
{
public:
	SampleGame() {}
	~SampleGame() {}

	const char* GetTitle() const override { return "サンプルゲーム"; }
	const char* GetVersion() const override { return "0.0.1"; }

	void StartRegister(const GameSystemCollection::GameSystemAdder& _pGameSystemAdder) override;
};
