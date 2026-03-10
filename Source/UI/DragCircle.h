#pragma once
#include <wtgb.h>

/// <summary>
/// 掴める円
/// </summary>
class DragCircle : public GameObject
{
public:
	DragCircle();
	DragCircle(const Vector2Int _centerPosition, const int _radius, const Vector2Int _baseCanvasSize = Vector2Int::Zero());
	~DragCircle();

	void Init() override;
	void Update() override;
	void Release() override;

	/// <summary>
	/// 掴んでいるかを取得
	/// </summary>
	/// <returns>掴んでいる true / false</returns>
	inline bool IsDrag() const { return isDrag_; }

	/// <summary>
	/// マウスが円内でクリックされたときのコールバック
	/// </summary>
	/// <param name="_callback"></param>
	inline void OnClickIn(const std::function<void()> _callback) { onClickInRadius_ = _callback; }
	/// <summary>
	/// マウスが円外でクリックされたときのコールバック
	/// </summary>
	/// <param name="_callback"></param>
	inline void OnClickOut(const std::function<void()> _callback) { onClickOutRadius_ = _callback; }
	/// <summary>
	/// マウスドラッグが終わったときのコールバック
	/// </summary>
	/// <param name="_callback"></param>
	inline void OnOut(const std::function<void()> _callback) { onOut_ = _callback; }

	/// <summary>
	/// 円の中心座標をセットする
	/// </summary>
	/// <param name="_centerPosition">円の中心座標</param>
	inline void SetPosition(const Vector2Int _centerPosition) { centerPosition_ = _centerPosition; }

	/// <summary>
	/// 比率維持のための設計時キャンバスサイズをセットする
	/// </summary>
	/// <param name="_baseCanvasSize">設計時のキャンバスサイズ</param>
	inline void SetBaseCanvasSize(const Vector2Int _baseCanvasSize) { baseCanvasSize_ = _baseCanvasSize; }

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
	Vector2Int baseCanvasSize_;    // 設計時のキャンバスサイズ
	TextureHandle hCircleImage_;   // 円の画像
	bool isDrag_;                  // 掴んでいるか
	Vector2Int centerPosition_;    // 円の中心座標
	Vector2Int dragBegin_;         // 掴んだ始点
	Vector2Int dragDisplacement_;  // 掴んだ大きさと方向
	int radius_;                   // 掴める円の半径
	int radiusSq_;                 // 掴める円の半径の2乗

	std::function<void()> onClickInRadius_;   // マウスがクリックされたコールバック 円の中
	std::function<void()> onClickOutRadius_;  // マウスがクリックされたコールバック 円の外
	std::function<void()> onOut_;  // ドラッグが離されたときのコールバック
};
