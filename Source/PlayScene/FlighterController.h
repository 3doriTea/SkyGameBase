#pragma once
#include <wtgb.h>


/// <summary>
/// リフトに追従するオブジェクトを管理
/// </summary>
class FlighterController : public GameObject
{
public:
	FlighterController(const EntityId _liftStructure, const EntityId _player);
	~FlighterController();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	EntityId liftStructure_;  // リフト本体
	EntityId player_;         // プレイヤー
};
