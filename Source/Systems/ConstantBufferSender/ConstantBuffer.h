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

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="_viewer">システム参照</param>
	void Initialize(const ViewerCached _viewer) override;

private:
	T buffer_{};                              // 構造体本体
	ComPtr<ID3D11Buffer> pConstantBuffer_{};  // コンスタントバッファ
};

template<typename T, ConstantBufferType ConstantBufferTypeV>
inline void ConstantBuffer<T, ConstantBufferTypeV>::Initialize(const ViewerCached _viewer)
{
	UINT cbSize = static_cast<UINT>(sizeof(T));
	// NOTE: 16byteアラインメントでのサイズにするために必要？
	cbSize = (cbSize + 15u) & ~15u;

	const D3D11_BUFFER_DESC CONSTANT_DESC
	{
		// 型の大きさ
		.ByteWidth = cbSize,
		.Usage = D3D11_USAGE_DYNAMIC,                // 変更するか
		.BindFlags = D3D11_BIND_CONSTANT_BUFFER,     // なんのバッファか
		.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE,    // CPUからのアクセスフラグ
		.MiscFlags = 0,                              // その他のフラグ
		.StructureByteStride = 0,
	};

	ID3D11Device* pDevice{ _viewer.Get<Direct3D>().Resource().Device() };
	ID3D11DeviceContext* pContext{ _viewer.Get<Direct3D>().Resource().Context() };
	HRESULT hResult{};

	hResult = pDevice->CreateBuffer(&CONSTANT_DESC, nullptr, pConstantBuffer_.GetAddressOf());
	wassert(SUCCEEDED(hResult) && "Fbxコンスタントバッファ作成に失敗");

	// VS、PSともにコンスタントバッファをセットする
	pContext->VSSetConstantBuffers(ConstantBufferTypeV, 1, pConstantBuffer_.GetAddressOf());  // 頂点シェーダ用
	pContext->PSSetConstantBuffers(ConstantBufferTypeV, 1, pConstantBuffer_.GetAddressOf());  // ピクセルシェーダ用
}
