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

	void OnLoadParam(const json& _json);

	void Init() override;
	void Update() override;

private:
	float timeLeft_;  // カウントダウン
	TextureHandle hSlideImage_;  // スライドしていく画像ハンドル
	Vector2Int cellSize_;  // １つの表示サイズ
};
