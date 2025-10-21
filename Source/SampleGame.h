#pragma once
#include <wtgb.h>

class SampleGame : public IGame
{
public:
	SampleGame() {}
	~SampleGame() {}

	const char* GetTitle() const override { return "ƒTƒ“ƒvƒ‹ƒQ[ƒ€"; }
	const char* GetVersion() const override { return "0.0.1"; }

	void StartRegister(const GameSystemCollection::GameSystemAdder& _pGameSystemAdder) override;
	void StartSetup(const GameSystemCollection::GameSystemInitViewer& _pGameSystemsViewer) override;
};
