#pragma once
#include <wtgb.h>

/// <summary>
/// スピード調整を行うUI
/// </summary>
class SpeedMeter : public GameObject
{
public:
	SpeedMeter(const EntityId _player);
	~SpeedMeter();

public:
	void Init() override;
	void Update() override;
	void Release() override;

private:
	EntityId player_;       // 速度を測るオブジェクト
	EntityId numberPlate_;  // 数字を表示するオブジェクト
};
