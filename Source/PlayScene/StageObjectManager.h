#pragma once
#include <wtgb.h>

/// <summary>
/// ステージ上のオブジェクトを管理する
/// </summary>
class StageObjectManager : public GameObject
{
public:
	StageObjectManager(const EntityId _stageLine, const EntityId _player, const EntityId _playState);
	~StageObjectManager();

	void Init() override;
	void Update() override;
	void Release() override;

	/// <summary>
	/// 爆発させる
	/// </summary>
	void Fire();

private:
	float spawnTimeLeftSec_;  // スポーンまでのカウントダウンタイマ
	EntityId stageLine_;      // ステージラインのエンティティId
	EntityId player_;         // プレイヤーのエンティティId
	EntityId playState_;      // プレイ状態
};

