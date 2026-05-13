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

	/// <summary>
	/// タイトル表示の猫の画像集
	/// </summary>
	enum IMAGE
	{
		I_HAND,  // 手の部分
		I_HANG,  // 引っ張られている胴体
		I_NORM,  // 普通の胴体
		I_MAX,   // 総数
	};
public:
	TitleNeco(
		const EntityId _dragCircle,
		const EntityId _fader,
		const EntityId _musicPlayer);
	~TitleNeco();

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

	/// <summary>
	/// ボタンが押された
	/// </summary>
	void OnPush();

private:
	TextureHandle hImages_[IMAGE::I_MAX];
	float moveRatio_;  // ムーブレート
	bool isDrag_;      // ドラッグ中か

	Vector2Int playButtonShowPos_;  // プレイボタンを表示させるときの位置

	EntityId dragPoint_;    // ドラッグして掴む円
	EntityId playButton_;   // プレイボタン
	EntityId fader_;        // フェーダー
	EntityId musicPlayer_;  // 音楽再生機

	TextureHandle hButtonOff_;  // ボタン画像 Off
	TextureHandle hButtonOn_;   // ボタン画像 On

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

	float toPlaySceneTime_;  // プレイシーンに遷移するまでの時間
};
