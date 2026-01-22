#pragma once
#include <wtgb.h>

/// <summary>
/// スピード調整を行うUI
/// </summary>
class SpeedMeter : public GameObject
{
public:
	SpeedMeter(const EntityId _target);
	~SpeedMeter();

public:
	void Init() override;
	void Update() override;
	void Release() override;

private:
	float speedValue_;

	EntityId target_;       // 速度を図るオブジェクト
	EntityId numberPlate_;  // 数字を表示するオブジェクト
};
