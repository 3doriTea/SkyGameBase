#pragma once
#include <wtgb.h>

/// <summary>
/// 当たり判定のタグ
/// </summary>
enum COLLIDER_TAG : uint32_t
{
	CT_PLAYER,  // プレイヤータグ
	CT_PRESENT_SPHERE,  // プレゼント球のタグ
};
