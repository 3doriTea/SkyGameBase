#pragma once
#include <wtgb.h>


/// <summary>
/// パーフェクトタイマのUI
/// </summary>
class PerfectTimer : public GameObject
{
public:
	PerfectTimer();
	~PerfectTimer();

	void Init() override;
	void Update() override;
	void Release() override;

	/// <summary>
	/// レートを指定する
	/// </summary>
	/// <param name="_ratio">レート 0.0f = 溜まっていない 1.0f = 演奏レベルアップ</param>
	void SetRatio(const float _ratio);

	void OnLoad(const json& _json);

private:
	float ratio_;   // パーフェクトタイマレート
	int height_;  // バーの高さ
	int margin_;  // マージン

	struct
	{
		Color backColor;        // 背景色
		Color thicknessColor;   // 縁の色
		Color fillColorNormal;  // 塗る色 普通
		Color fillColorFull;    // 塗る色 満タン
	} bar_;  // バー
};
