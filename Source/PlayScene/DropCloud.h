#pragma once
#include <wtgb.h>
#include "SMF/Note.h"

/// <summary>
/// アイテムを降らせる雲
/// </summary>
class DropCloud : public GameObject
{
private:
	/// <summary>
	/// 投下したプレゼント情報
	/// </summary>
	struct DropedPresent
	{
		EntityId entityId;  // エンティティ
		Note note;  // ノーツ情報
	};

public:
	DropCloud(
		const EntityId _smfPlayer,
		const EntityId _gamePlayer,
		const EntityId _stageLine,
		const EntityId _playState);
	~DropCloud();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	/// <summary>
	/// jsonからパラメータを読み込む
	/// </summary>
	/// <param name="_json">パラメータのjson</param>
	void OnLoadParam(const json& _json);

private:
	EntityId smfPlayer_;  // smfPlayer
	EntityId player_;     // プレイヤー
	EntityId stageLine_;  // ステージ
	EntityId playState_;  // プレイ状態

	float offsetHeight_;  // 地上からの高さ

	float destroyDistanceZ_;    // プレイヤーとの距離が離れたときに消す処理
	int playNoteNumberOffset_;  // 再生する音の高さ

	std::list<DropedPresent> dropedPresents_;  // 投下したプレゼントリスト
};
