#pragma once
#include <wtgb.h>
#include "ConstantBufferType.h"

/// <summary>
/// コンスタントバッファのインタフェース
/// </summary>
class IConstantBuffer
{
public:
	IConstantBuffer() = default;
	virtual ~IConstantBuffer() = default;

	/// <summary>
	/// サイズを取得する
	/// </summary>
	/// <returns>型のサイズ</returns>
	virtual const UINT GetSize() const = 0;

	/// <summary>
	/// バッファのポインタを取得する
	/// </summary>
	/// <returns>バッファのポインタ</returns>
	virtual const void* GetPtr() const = 0;

	/// <summary>
	/// コンスタントバッファ構造体の型インデクスを取得する
	/// </summary>
	/// <returns>コンスタントバッファ構造体の型インデクス</returns>
	virtual const std::type_index GetType() const = 0;

	/// <summary>
	/// コンスタントバッファの種類を取得する
	/// </summary>
	/// <returns>コンスタントバッファの種類</returns>
	virtual const ConstantBufferType GetConstantBufferType() const = 0;

	/// <summary>
	/// コンスタントバッファの参照を取得する
	/// </summary>
	/// <returns>コンスタントバッファの参照ポインタ</returns>
	virtual ComPtr<ID3D11Buffer>& GetConstantBuffer() = 0;
};
