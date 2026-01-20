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
	EntityId smfPlayer_;  // smfPlayer
	EntityId player_;     // プレイヤー
	EntityId stageLine_;  // ステージ
	EntityId playState_;  // プレイ状態

	float offsetHeight_;  // 地上からの高さ

	std::list<DropedPresent> dropedPresents_;  // 投下したプレゼントリスト
};
