#pragma once
#include <wtgb.h>


/// <summary>
/// はねねこボール
/// </summary>
class NekoGame : public IGame
{
public:
	NekoGame() {}
	~NekoGame() {}

	inline const char8_t* GetTitle() const override { return u8"はねねこ ボール"; }
	inline const char8_t* GetVersion() const override { return u8"1.1.1"; }

	void StartRegister(const GameSystemCollection::GameSystemAdder& _pGameSystemAdder) override;
};
