#pragma once
#include <wtgb.h>
#include "ConstantBuffer.h"

/// <summary>
/// ステージのコンスタントバッファ構造体
/// </summary>
struct StageConstantBuffer_
{
	DirectX::XMFLOAT4 uvRatio;  // UV座標のレート
};

/// <summary>
/// ステージのコンスタントバッファ
/// </summary>
using StageConstantBuffer = ConstantBuffer<
	StageConstantBuffer_,
	ConstantBufferType_Stage>;
