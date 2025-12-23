#pragma once
#include <wtgb.h>

/// <summary>
/// アイテムを降らせる雲
/// </summary>
class DropCloud : public GameObject
{
public:
	DropCloud(
		const EntityId _smfPlayer,
		const EntityId _gamePlayer,
		const EntityId _stageLine);
	~DropCloud();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	EntityId smfPlayer_;  // smfPlayer
	EntityId player_;     // プレイヤー
	EntityId stageLine_;  // ステージ

	float offsetHeight_;  // 地上からの高さ
};
