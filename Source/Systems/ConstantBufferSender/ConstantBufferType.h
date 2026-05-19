#pragma once
#include <wtgb.h>

/// <summary>
/// コンスタントバッファの種類
/// </summary>
using ConstantBufferType = uint32_t;

/// <summary>
/// コンスタントバッファの種類
/// </summary>
enum ConstantBufferType_ : ConstantBufferType
{
	ConstantBufferType_Global = 0,  // グローバルな定数 3D/2D両対応
	ConstantBufferType_Post = 1,    // ポストプロセシング用
	ConstantBufferType_Player = 2,  // プレイヤーの情報
	ConstantBufferType_Max,         // コンスタントバッファの最大数
};
