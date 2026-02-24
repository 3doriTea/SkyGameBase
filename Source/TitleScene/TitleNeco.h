#pragma once
#include <wtgb.h>


/// <summary>
/// タイトルシーンの猫
/// </summary>
class TitleNeco : public GameObject
{
	enum IMAGE
	{
		I_HAND,
		I_HANG,
		I_NORM,
		I_MAX,
	};
public:
	TitleNeco(const EntityId _dragCircle);
	~TitleNeco();

	void Init() override;
	void Update() override;
	void Release() override;

	/// <summary>
	/// 移動レートを取得する
	/// </summary>
	/// <returns>移動レート 0.0 .. 1.0</returns>
	float GetMoveRaito() const { return moveRatio_; }

private:
	/// <summary>
	/// jsonからパラメータを読み込む
	/// </summary>
	/// <param name="_json">パラメータのjson</param>
	void OnLoadParam(const json& _json);

private:
	TextureHandle hImages_[IMAGE::I_MAX];
	float moveRatio_;  // ムーブレート
	bool isDrag_;  // ドラッグ中か

	Vector2Int playButtonShowPos_;  // プレイボタンを表示させるときの位置

	EntityId dragPoint_;  // ドラッグして掴む円
	EntityId playButton_;  // プレイボタン

	TextureHandle hButtonOff_;
	TextureHandle hButtonOn_;

	std::string playToneAudioFile_;  // トーンとして流す音のファイルパス

	int uiLayoutConfigOrder_;  // UIレイアウト設定の描画順番
};
