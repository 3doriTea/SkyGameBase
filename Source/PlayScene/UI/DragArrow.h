#pragma once
#include <wtgb.h>

/// <summary>
/// プレイヤーに付いている矢印
/// </summary>
using DragArrowType = int32_t;
enum DragArrowType_
{
	DragArrowType_Control,   // 加速度を表す
	DragArrowType_Velocity,  // 速度を表す
	DragArrowType_Max,       // 最大数
};

/// <summary>
/// ドラッグした方向が分かる3D UI
/// </summary>
class DragArrow : public GameObject
{
public:
	DragArrow(const EntityId _axis);
	~DragArrow();

	void Init() override;
	void Update() override;
	void Release() override;

	/// <summary>
	/// 矢印の種類を変更する
	/// </summary>
	/// <param name="type">矢印の種類</param>
	void ChangeType(const DragArrowType _type);

	void OnLoadParam(const json& _json);

private:
	DragArrowType type_;  // 矢印の種類
	Vector2 direction_;   // 矢印ノーマル
	EntityId axis_;       // 軸

	// 矢印のテクスチャ
	TextureHandle hTexture_[DragArrowType_Max];
};
