#pragma once
#include <wtgb.h>

/// <summary>
/// ドラッグ矢印の軸
/// </summary>
class DragArrowAxis : public GameObject
{
public:
	DragArrowAxis(const EntityId _player);
	~DragArrowAxis();

	void Init() override;
	void Update() override;
	void Release() override;

	/// <summary>
	/// スケールZをセットする
	/// </summary>
	/// <param name="_z">Zの大きさ</param>
	void SetScaleZ(const float _z);

	/// <summary>
	/// 回転Yをセットする
	/// </summary>
	/// <param name="_angle">回転角度</param>
	void SetAngleY(const float _angle);

private:
	void OnLoad(const json& _j);

private:
	EntityId player_;  // プレイヤーエンティティ
	float scaleBase_;  // スケールのベース
	float scaleZDiv_;  // スケールZの分母
};
