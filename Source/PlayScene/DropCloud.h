#pragma once
#include <wtgb.h>
#include "SMF/Note.h"
#include "CloudLevel.h"
#include "UI/MiniCharaType.h"


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
		const EntityId _miniCharaManager,
		const EntityId _faderController);
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

	/// <summary>
	/// プレゼントを投下する
	/// </summary>
	/// <param name="_note">ノーツ情報</param>
	void DropPresent(const Note _note);

private:
	EntityId smfPlayer_;         // smfPlayer
	EntityId player_;            // プレイヤー
	EntityId stageLine_;         // ステージ
	EntityId playState_;         // プレイ状態
	EntityId speedController_;   // プレイ状態
	EntityId miniCharaManager_;  // ミニキャラ統括
	EntityId faderController_;   // フェーダコントローラ

	float toResultSceneTime_;  // 再生終了後、結果シーンに遷移するまでの秒数
	float offsetHeight_;  // 地上からの高さ

	float destroyDistanceZ_;    // プレイヤーとの距離が離れたときに消す処理
	int playNoteNumberOffset_;  // 再生する音の高さ

	float dropDistanceZ_;  // ノーツを投下するときのプレイヤーからの距離z

	float playRatioMaxVelocity_;  // 再生レートを変動させる最大速度

	std::string playSMFPath_;  // 再生する smf

	// 各音色のファイル
	std::array<std::string, MiniCharaType_Max> toneAudioFilesPath_;
	
	std::list<DroppedPresent> droppedPresents_;  // 投下したプレゼントリスト

	bool isFinished_;  // 全ボールを出し終えたか

	// 各ミニキャラの音色の音声ファイル
	std::array<AudioHandle, MiniCharaType_Max> hAudios_;

	CloudLevel level_;    // うまく演奏していると上がるレベル
	float perfectTimer_;  // ノーミスの秒数
	int prevBar_;         // 前のフレームでの小節

	EntityId perfectTimerUI_;  // 完璧継続を表示するUI
};
