#pragma once
#include "Utility/IResource.h"

namespace wtgb
{
	class IMeshSimple : public IResource
	{
	public:
		IMeshSimple();
		virtual ~IMeshSimple();

		virtual void Init() = 0;
		virtual void Release() = 0;

protected:
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
