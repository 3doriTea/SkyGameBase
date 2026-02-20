#pragma once
#include <wtgb.h>

/// <summary>
/// カウントダウンUI
/// </summary>
class CountDown : public GameObject
{
public:
	CountDown();
	~CountDown();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	/// <summary>
	/// GOのときのアニメーション
	/// </summary>
	void PlayAnimGo(RectF& _rectF);
	void PlayAnimCountDown(RectF& _rectF);
	void OnLoadParam(const json& _json);

private:
	float timeLeft_;                // カウントダウン
	float timeScaleSec_;            // ダウンしていく秒数
	float moveTimeRatio_;           // ダウンしていく秒数のうち動いている割合
	TextureHandle hSlideImage_;     // スライドしていく画像ハンドル
	Vector2Int cellSize_;           // １つの表示サイズ
	Vector2Int imageSize_;          // 画像のサイズ
	Vector2Int baseSize_;           // UI配置の基準となるサイズ
	Vector2Int drawPos_;            // 描画する左上座標
	Vector2Int smallingPerFScale_;  // GOアニメーション時, 1フレームで小さくなるサイズ
};
