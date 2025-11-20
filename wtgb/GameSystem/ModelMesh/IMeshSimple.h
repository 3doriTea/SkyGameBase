#pragma once
#include "Utility/IResource.h"

namespace wtgb
{
	class IMeshSimple : public IResource
	{
	public:
		IMeshSimple();
		virtual ~IMeshSimple();

		virtual void Init() override = 0;
		virtual void Release() override = 0;
		virtual size_t GetVertexSize() = 0;

		/// <summary>
		/// 頂点バッファを取得する
		/// </summary>
		/// <returns>頂点バッファ</returns>
		virtual ComPtr<ID3D11Buffer>& GetVertexBuffer() = 0;
		/// <summary>
		/// インデックスバッファを取得する
		/// </summary>
		/// <returns>インデックスバッファ</returns>
		virtual ComPtr<ID3D11Buffer>& GetIndexBuffer() = 0;
		/// <summary>
		/// コンスタントバッファを取得する
		/// </summary>
		/// <returns>コンスタントバッファ</returns>
		virtual ComPtr<ID3D11Buffer>& GetConstantBuffer() = 0;
	};
}
