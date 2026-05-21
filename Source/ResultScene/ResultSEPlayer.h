#pragma once
#include <wtgb.h>

/// <summary>
/// 結果の効果音を再生する
/// </summary>
class ResultSEPlayer : public GameObject
{
public:
	ResultSEPlayer();
	~ResultSEPlayer();

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
	AudioHandle hClearSound_;   // ゲームクリア時のサウンド
	AudioHandle hFailedSound_;  // ゲーム失敗時のサウンド
};
