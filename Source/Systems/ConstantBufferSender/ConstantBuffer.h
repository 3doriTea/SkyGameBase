#pragma once
#include "IConstantBuffer.h"

/// <summary>
/// <para>コンスタントバッファのラップクラス</para>
/// <para>struct Hoge_{ ... }; using Hoge = ConstantBuffer<Hoge_>;</para>
/// <para>と記述して使う</para>
/// </summary>
/// <typeparam name="T">型</typeparam>
/// <typeparam name="ConstantBufferTypeV">コンスタントバッファの種類</typeparam>
template<typename T, ConstantBufferType ConstantBufferTypeV>
class ConstantBuffer final : public IConstantBuffer
{
public:
	ConstantBuffer() = default;
	~ConstantBuffer() = default;

	/// <summary>
	/// サイズを取得する
	/// </summary>
	/// <returns>型のサイズ</returns>
	inline const UINT GetSize() const override { return static_cast<UINT>(sizeof(T)); }

	/// <summary>
	/// バッファのポインタを取得する
	/// </summary>
	/// <returns>バッファのポインタ</returns>
	inline const void* GetPtr() const override { return &buffer_; }

	/// <summary>
	/// バッファの構造体を直接参照する
	/// </summary>
	/// <returns>バッファの構造体を直接参照する</returns>
	inline T& Ref() { return buffer_; }

	/// <summary>
	/// コンスタントバッファ構造体の型インデクスを取得する
	/// </summary>
	/// <returns>コンスタントバッファ構造体の型インデクス</returns>
	inline const std::type_index GetType() const { return std::type_index{ typeid(T) }; };

	/// <summary>
	/// コンスタントバッファの種類を取得する
	/// </summary>
	/// <returns>コンスタントバッファの種類</returns>
	inline const ConstantBufferType GetConstantBufferType() const override { return ConstantBufferTypeV; }

	/// <summary>
	/// コンスタントバッファの参照を取得する
	/// </summary>
	/// <returns>コンスタントバッファの参照ポインタ</returns>
	inline virtual ComPtr<ID3D11Buffer>& GetConstantBuffer() override { return pConstantBuffer_; }

private:
	T buffer_{};                              // 構造体本体
	ComPtr<ID3D11Buffer> pConstantBuffer_{};  // コンスタントバッファ
};
