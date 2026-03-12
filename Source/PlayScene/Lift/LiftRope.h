#pragma once
#include <wtgb.h>
#include "LiftRopeMesh.h"


/// <summary>
/// リフトのロープ部分
/// </summary>
class LiftRope : public GameObject
{
public:
	LiftRope(const Vector3& _position, const EntityId _stageLine, const EntityId _structure);
	~LiftRope();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	std::vector<Vector2> points_;  // 各頂点の座標 (xy平面で考える)
	LiftRopeMesh ropeMesh_;        // ロープのメッシュ情報
	EntityId stageLine_;           // ステージライン
	EntityId structure_;           // リフト本体
};
