#pragma once
#include "IMiniCharaState.h"


/// <summary>
/// ミニキャラ: ベース3
/// </summary>
class MiniCharaGlocken : public IMiniCharaState
{
public:
	MiniCharaGlocken() = default;
	~MiniCharaGlocken() = default;

	void Init(MiniChara& _self) override;
	void Update(MiniChara& _self) override;
};
