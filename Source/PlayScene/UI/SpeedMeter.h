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
	void OnLoadParam(const json& _json);

private:
	EntityId player_;       // 速度を測るオブジェクト
	EntityId numberPlate_;  // 数字を表示するオブジェクト

	Vector2Int baseCanvasSize_;     // UI設計時のキャンバスサイズ
	int numbersCenterOffset_;       // スピード数字の中心からずらす分
	std::string numbersImageFile_;  // 数字の画像
};
