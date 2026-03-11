#pragma once
#include <wtgb.h>


/// <summary>
/// サンプルゲーム
/// </summary>
class SampleGame : public IGame
{
public:
	SampleGame() {}
	~SampleGame() {}

	inline const char8_t* GetTitle() const override { return u8"Sample Game"; }
	inline const char8_t* GetVersion() const override { return u8"0.0.1"; }

	void StartRegister(const GameSystemCollection::GameSystemAdder& _pGameSystemAdder) override;
};
