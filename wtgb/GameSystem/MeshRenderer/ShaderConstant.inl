#include "GameSystem/Direct3D.h"
#include "WTGBAssert.h"
#include "ShaderConstant.h"


template<typename StructT>
inline wtgb::ShaderConstant<StructT>::ShaderConstant() :
	pConstantBuffer_{ nullptr },
	beginSlot_{},
	SlotCount_{ 1 }
{
}

template<typename StructT>
inline wtgb::ShaderConstant<StructT>::~ShaderConstant()
{
}

template<typename StructT>
inline void wtgb::ShaderConstant<StructT>::Init(ViewerCached _system)
{
	UINT cbSize = static_cast<UINT>(sizeof(StructT));

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

	ID3D11Device* pDevice{ _system.Get<Direct3D>().Resource().Device() };
	HRESULT hResult{};

	hResult = pDevice->CreateBuffer(&CONSTANT_DESC, nullptr, pConstantBuffer_.GetAddressOf());
	wassert(SUCCEEDED(hResult) && "ShaderConstantのコンスタントバッファ作成に失敗");

}

template<typename StructT>
inline void wtgb::ShaderConstant<StructT>::Send(ViewerCached _system)
{
	// TODO: コンスタントバッファを何度もセットするのは無駄だとは思いつつ

	Direct3D& d3d{ _system.Get<Direct3D>() };
	ID3D11Device* pDevice{ d3d.Resource().Device() };
	ID3D11DeviceContext* pContext{ d3d.Resource().Context() };

	// コンスタントバッファをセット
	pContext->VSSetConstantBuffers(beginSlot_, slotCount_, pConstantBuffer_.GetAddressOf());  // 頂点シェーダ用
	pContext->PSSetConstantBuffers(beginSlot_, slotCount_, pConstantBuffer_.GetAddressOf());  // ピクセルシェーダ用

	D3D11_MAPPED_SUBRESOURCE data{};

	pContext->Map(pConstantBuffer_.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	memcpy_s(
		data.pData,
		data.RowPitch,
		reinterpret_cast<void*>(&pConstantBuffer_),
		sizeof(StructT));
	pContext->Unmap(pConstantBuffer_.Get(), 0);
}
