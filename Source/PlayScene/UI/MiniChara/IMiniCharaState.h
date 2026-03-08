#pragma once

class MiniChara;

struct IMiniCharaState
{
public:
	IMiniCharaState() = default;
	~IMiniCharaState() = default;

	virtual void Init(MiniChara& _self) = 0;
	virtual void Update(MiniChara& _self) = 0;
};
