#pragma once
#include "IMiniCharaState.h"


/// <summary>
/// ミニキャラ: モンキティ
/// </summary>
class MiniCharaMonkitty : public IMiniCharaState
{
public:
	MiniCharaMonkitty() = default;
	~MiniCharaMonkitty() = default;

	void Init(MiniChara& _self) override;
	void Update(MiniChara& _self) override;
};
