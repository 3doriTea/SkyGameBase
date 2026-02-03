#pragma once
#include <wtgb.h>

/// <summary>
/// ドラッグできるポイントUI
/// </summary>
class DragPoint : public GameObject
{
public:
	DragPoint();
	~DragPoint();

	void Init() override;
	void Update() override;
	void Release() override;

	/// <summary>
	/// 掴んでいるかを取得
	/// </summary>
	/// <returns>掴んでいる true / false</returns>
	inline bool IsDrag() const { return isDrag_; }

	/// <summary>
	/// 円の中心座標をセットする
	/// </summary>
	/// <param name="_centerPosition">円の中心座標</param>
	inline void SetPosition(const Vector2Int _centerPosition) { centerPosition_ = _centerPosition; }
	/// <summary>
	/// 円の半径をセットする
	/// </summary>
	/// <param name="_radius">円の半径</param>
	void SetRadius(const int _radius);

	/// <summary>
	/// ドラッグのベクトルを取得する
	/// </summary>
	/// <returns></returns>
	inline Vector2Int GetDisplacement() const { return dragDisplacement_; }
	/// <summary>
	/// ドラッグの開始地点を取得する
	/// </summary>
	/// <returns>開始地点の座標</returns>
	inline Vector2Int GetBegin() const { return dragBegin_; }

private:
	Vector2Int centerPosition_;  // ドラッグポイントのスクリーン座標
	float radius_;               // ドラッグできる範囲
	float radiusSq_;             // ドラッグできる範囲の二乗

	bool isDrag_;                  // ドラッグ中か true / false
	Vector2Int dragBegin_;         // 掴んだ始点
	Vector2Int dragDisplacement_;  // 掴んだ大きさと方向
};
