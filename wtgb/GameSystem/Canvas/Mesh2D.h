#pragma once
#include "pch/pch.h"
#include "../ModelMesh/IMeshSimple2D.h"

namespace wtgb
{
	class Mesh2D : public IMeshSimple2D
	{
	public:
		Mesh2D();
		~Mesh2D();

		void Init(ViewerCached _system) override;
		void Release(ViewerCached _system) override;

		ComPtr<ID3D11Buffer>& GetVertexBuffer() override { return pVertexBuffer_; }
		ComPtr<ID3D11Buffer>& GetIndexBuffer() override { return pIndexBuffer_; }
		ComPtr<ID3D11Buffer>& GetConstantBuffer() override { return pConstantBuffer_; }
		/// <summary>
		/// 頂点のサイズを取得
		/// </summary>
		/// <returns>頂点の構造体サイズ(byte)</returns>
		size_t GetVertexSize() const override { return sizeof(Vertex); }

		/// <summary>
		/// 頂点数を取得する
		/// </summary>
		/// <returns></returns>
		uint32_t GetVertexCount() const override { return vertexCount_; }

		/// <summary>
		/// インデックス数を取得する
		/// </summary>
		/// <returns>インデックス数</returns>
		uint32_t GetIndexCount() const override { return indexCount_; }

		/// <summary>
		/// テクスチャハンドルを取得する
		/// </summary>
		/// <returns></returns>
		TextureHandle GetTextureHandle() const override { return hTexture_; }

	private:
		uint32_t vertexCount_;  // 頂点数
		uint32_t indexCount_;   // インデックス数

		TextureHandle hTexture_;  // テクスチャのハンドル

		ComPtr<ID3D11Buffer> pVertexBuffer_;    // 頂点バッファ
		ComPtr<ID3D11Buffer> pIndexBuffer_;     // インデックスバッファ
		ComPtr<ID3D11Buffer> pConstantBuffer_;  // コンスタントバッファ
	};
}
