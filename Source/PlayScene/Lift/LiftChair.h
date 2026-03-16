#pragma once
#include <wtgb.h>

/// <summary>
/// リフトのかごである椅子オブジェクト
/// </summary>
class LiftChair : public GameObject
{
public:
	LiftChair(const EntityId _structure, const float _beginLength, const float _maxLength);
	~LiftChair();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	EntityId structure_;    // リフト本体
	float length_;          // 再生中の長さ
	float lengthMax_;       // 全体の長さ
};
