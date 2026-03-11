#pragma once
#include "IMiniCharaState.h"


/// <summary>
/// ミニキャラ: チューバー
/// </summary>
class MiniCharaTubar : public IMiniCharaState
{
public:
	MiniCharaTubar() = default;
	~MiniCharaTubar() = default;

	void Init(MiniChara& _self) override;
	void Update(MiniChara& _self) override;
};
