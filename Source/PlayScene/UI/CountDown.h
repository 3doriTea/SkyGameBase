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

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 解放処理
	/// </summary>
	void Release() override;

private:
	/// <summary>
	/// 描画矩形をカウントダウン後GO中のアニメーションで変更
	/// </summary>
	/// <param name="_rectF">変更する矩形</param>
	/// <param name="_deltaTime">Goアニメーションの秒数</param>
	void PlayAnimGo(RectF& _rectF, const float _deltaTime);
	/// <summary>
	/// 描画矩形をカウントダウン中のアニメーションで変更
	/// </summary>
	/// <param name="_rectF">変更する矩形</param>
	void PlayAnimCountDown(RectF& _rectF);
	/// <summary>
	/// パラメータを読み込む
	/// </summary>
	/// <param name="_json">jsonパラメータ</param>
	void OnLoadParam(const json& _json);

private:
	float timeLeft_;             // カウントダウン
	float timeScaleSec_;         // ダウンしていく秒数
	float moveTimeRatio_;        // ダウンしていく秒数のうち動いている割合
	TextureHandle hSlideImage_;  // スライドしていく画像ハンドル
	Vector2 cellSize_;           // １つの表示サイズ
	Vector2Int imageSize_;       // 画像のサイズ
	Vector2Int baseSize_;        // UI配置の基準となるサイズ
	Vector2Int drawPos_;         // 描画する左上座標
	Vector2 smallingPerFScale_;  // GOアニメーション時, 1フレームで小さくなるサイズ
};
