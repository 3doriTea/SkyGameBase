#pragma once
#include <wtgb.h>

class SampleGame : public IGame
{
public:
	SampleGame() {}
	~SampleGame() {}

	std::string GetTitle() const override { return "ƒTƒ“ƒvƒ‹ƒQ[ƒ€"; }
	std::string GetVersion() const override { return "0.0.1"; }

	void Start(GameSystemCollection* _pGameSystemRegister) override;
};
