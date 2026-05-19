#pragma once
#include <wtgb.h>
#include "ConstantBuffer.h"

/// <summary>
/// プレイヤーのコンスタントバッファ構造体
/// </summary>
struct PlayerConstantBuffer_
{
	DirectX::XMFLOAT4 position;  // プレイヤーの座標
};

/// <summary>
/// プレイヤーのコンスタントバッファ
/// </summary>
using PlayerConstantBuffer = ConstantBuffer<
	PlayerConstantBuffer_,
	ConstantBufferType_Player>;
