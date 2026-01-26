#pragma once
#include <wtgb.h>


/// <summary>
/// キャラがかぶっているボール
/// </summary>
class BallSphere : public GameObject
{
public:
	BallSphere(const EntityId _targetChara);
	~BallSphere();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	EntityId targetChara_;  // 追従するキャラ
};
