#pragma once
#include <wtgb.h>


/// <summary>
/// タイトルシーンの猫
/// </summary>
class TitleNeco : public GameObject
{
	/// <summary>
	/// ムーブレートのパラメータ
	/// </summary>
	struct MoveRatioConfig
	{
		float autoMovingRatio;
		float dtDiv;
		float moveRatioMin;
		float moveRatioMax;
	};

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

	MoveRatioConfig moveRatioConfig_;  // ムーブレートの設定

	int dragCircleRadius_;
	int playButtonRadius_;
	int playNoteChannel_;
	int playNoteDiffOffset_;

	int dragCircleOffsetX_;                 // ドラッグ円のx座標
	int dragCircleOffsetXPP_;               // ドラッグ円のx座標++
	float dragCircleOffsetScreenSizeYDiv_;  // ドラッグ円のy座標 スクリーンサイズyとの割合
};
