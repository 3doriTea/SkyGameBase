#pragma once
#include "Utility/IResource.h"


namespace wtgb
{
	template<typename T>
	class ConstantBufferBox final : public IResource<ViewerCached>
	{
		static_assert(alignof(T) == 16, "16byte アラインメントである必要があります。");
	public:
		inline ConstantBufferBox() {}
		inline ~ConstantBufferBox() {}

		inline ComPtr<ID3D11Buffer>& GetConstantBuffer() { return pConstantBuffer_; }

	private:
		inline void Init(ViewerCached _viewer) override
		{
			UINT cbSize = static_cast<UINT>(sizeof(ConstantBuffer));
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

			ID3D11Device* pDevice{ _system.Get<Direct3D>().Resource().Device() };
			HRESULT hResult{};

			hResult = pDevice->CreateBuffer(&CONSTANT_DESC, nullptr, pConstantBuffer_.GetAddressOf());
			wassert(SUCCEEDED(hResult) && "Fbxコンスタントバッファ作成に失敗");
		}
		
		inline void Release(ViewerCached _viewer) override
		{
		}

	private:
		ComPtr<ID3D11Buffer> pConstantBuffer_;  // コンスタントバファ

	};
}
