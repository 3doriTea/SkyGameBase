#pragma once
#include <wtgb.h>

/// <summary>
/// ステージ上のオブジェクトを管理する
/// </summary>
class StageObjectManager : public GameObject
{
public:
	StageObjectManager(const EntityId _stageLine, const EntityId _player);
	~StageObjectManager();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	EntityId stageLine_;  // ステージラインのエンティティId
	EntityId player_;     // プレイヤーのエンティティId
};

