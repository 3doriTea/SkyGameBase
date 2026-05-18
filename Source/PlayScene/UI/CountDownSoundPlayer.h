#pragma once
#include <wtgb.h>

/// <summary>
/// カウントダウン時の効果音を再生する
/// </summary>
class CountDownSoundPlayer : public GameObject
{
public:
	CountDownSoundPlayer();
	~CountDownSoundPlayer();

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
	/// パラメータを読み込む
	/// </summary>
	/// <param name="_json">jsonパラメータ</param>
	void OnLoadParam(const json& _json);

private:
	AudioHandle hSoundHigh_;  // 高音の音声ハンドル
	AudioHandle hSoundLow_;   // 低温の音声ハンドル
	float timeLeft_;          // 残り時間
	int prevTimeLeftSec_;     // 前回の時間(秒部分)
};
