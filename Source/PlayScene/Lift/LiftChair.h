#pragma once
#include <wtgb.h>

/// <summary>
/// リフトのかごである椅子オブジェクト
/// </summary>
class LiftChair : public GameObject
{
public:
	LiftChair(const EntityId _lift, const float _beginZ, const bool _beginIsUpping);
	~LiftChair();

	void Init() override;
	void Update() override;
	void Release() override;

	/// <summary>
	/// 転回開始
	/// </summary>
	void StartUTurn();

	/// <summary>
	/// 転回終了
	/// </summary>
	void EndUTurn();

private:
	EntityId lift_;    // リフト本体
	float positionZ_;  // リフトの場所
	bool isUpping_;    // 登り方向か否か
	bool isRotating_;  // 回転中か
};
