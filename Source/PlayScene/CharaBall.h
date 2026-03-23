#pragma once
#include <wtgb.h>

/// <summary>
/// 集めた仲間のボール
/// </summary>
class CharaBall : public GameObject
{
public:
	CharaBall(const Vector3& _position, const Vector3& _velocity, const EntityId _player);
	~CharaBall();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	EntityId player_;  // プレイヤー
};

