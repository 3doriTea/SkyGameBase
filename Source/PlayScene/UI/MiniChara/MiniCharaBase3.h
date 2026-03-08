#pragma once
#include "IMiniCharaState.h"


/// <summary>
/// ミニキャラ: ベース3
/// </summary>
class MiniCharaBase3 : public IMiniCharaState
{
public:
	MiniCharaBase3() = default;
	~MiniCharaBase3() = default;

	void Init(MiniChara& _self) override;
	void Update(MiniChara& _self) override;
};
