#pragma once
#include <wtgb.h>
#include "SMF/Note.h"
#include "CloudLevel.h"


/// <summary>
/// アイテムを降らせる雲
/// </summary>
class DropCloud : public GameObject
{
private:
	/// <summary>
	/// 投下したプレゼント情報
	/// </summary>
	struct DroppedPresent
	{
		EntityId entityId;  // エンティティ
		Note note;          // ノーツ情報
		AudioHandle hTone;  // 音源
		int32_t toneOffset;    // トーンのオフセット
	};

public:
	DropCloud(
		const EntityId _smfPlayer,
		const EntityId _gamePlayer,
		const EntityId _stageLine,
		const EntityId _playState,
		const EntityId _speedController,
		const EntityId _miniCharaManager);
	~DropCloud();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	/// <summary>
	/// jsonからパラメータを読み込む
	/// </summary>
	/// <param name="_json">パラメータの json</param>
	void OnLoadParam(const json& _json);

private:
	EntityId smfPlayer_;         // smfPlayer
	EntityId player_;            // プレイヤー
	EntityId stageLine_;         // ステージ
	EntityId playState_;         // プレイ状態
	EntityId speedController_;   // プレイ状態
	EntityId miniCharaManager_;  // ミニキャラ統括

	float toResultSceneTime_;  // 再生終了後、結果シーンに遷移するまでの秒数
	float offsetHeight_;  // 地上からの高さ

	float destroyDistanceZ_;    // プレイヤーとの距離が離れたときに消す処理
	int playNoteNumberOffset_;  // 再生する音の高さ

	float dropDistanceZ_;  // ノーツを投下するときのプレイヤーからの距離z

	float playRatioMaxVelocity_;  // 再生レートを変動させる最大速度

	std::string playSMFPath_;  // 再生する smf
	std::string playToneAudioFilePath_;     // 再生する音の音源ファイル
	std::string toneAudioFilePathBase_;     // 再生するベース音の音源ファイル
	std::string toneAudioFilePathTuba_;     // 再生するチューバ音の音源ファイル
	std::string toneAudioFilePathDrum_;     // 再生するドラム音の音源ファイル
	std::string toneAudioFilePathGlocken_;  // 再生するグロッケン音の音源ファイル

	std::list<DroppedPresent> droppedPresents_;  // 投下したプレゼントリスト

	bool isFinished_;  // 全ボールを出し終えたか

	AudioHandle hAudioCat_;  // 猫音
	AudioHandle hAudioBase_;  // ベース音
	AudioHandle hAudioTuba_;  // チューバ音
	AudioHandle hAudioDrum_;  // ドラム音
	AudioHandle hAudioGlocken_;  // グロッケンシュピール音

	CloudLevel level_;    // うまく演奏していると上がるレベル
	float perfectTimer_;  // ノーミスの秒数
	int prevBar_;         // 前のフレームでの小節
};
