#pragma once
#include <wtgb.h>

/// <summary>
/// スペシャルボム
/// </summary>
class SpecialBoom : public GameObject
{
public:
	SpecialBoom(const Vector3& _position, const EntityId _stageObjManager, const EntityId _player);
	~SpecialBoom();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	EntityId stageObjManager_;
	EntityId player_;
};
