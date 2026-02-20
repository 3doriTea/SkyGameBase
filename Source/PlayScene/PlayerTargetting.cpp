#include "PlayerTargetting.h"

Vector3 PlayerTargeting::GetToTargetVelocity(const PLAYER_TARGETTING_PARAMS& params)
{
	using namespace DirectX;

	const auto&[pPos, pVel, tPos, g]{ params };

	// ターゲットまでの距離
	float dist{ XMVectorGetX(XMVector3Length(tPos - pPos)) };
	// 現在の速度
	float speed{ XMVectorGetX(XMVector3Length(pVel)) };

	float t{ dist / speed };

	float up{ 0.0f };
	if (tPos.y < pPos.y)  // プレイヤーの位置が高い
	{
		up = (g * t) / 2.0f;
	}

	return
	{
		(tPos.x - pPos.x) / t,
		(tPos.y - pPos.y) / t + up,
		(tPos.z - pPos.z) / t,
	};
}
