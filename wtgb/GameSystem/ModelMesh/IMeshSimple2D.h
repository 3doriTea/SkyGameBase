#pragma once
#include "Utility/IResource.h"
#include "Core/GameSystemViewer.h"

namespace wtgb
{
	/// <summary>
	/// 2D用シンプルなメッシュ
	/// </summary>
	class IMeshSimple2D : public IResource<ViewerCached>
	{
	public:
		/// <summary>
		/// 頂点情報
		/// </summary>
		struct Vertex
		{
			Vector4 position;
			Vector4 uv;
		};

		/// <summary>
		/// コンスタントバッファ
		/// </summary>
		struct ConstantBuffer
		{
			Matrix4x4 matrixProj;          // プロジェクションの合成行列
			Matrix4x4 matrixUV;            // UV変換行列
			Color color;                   // テクスチャが無い場合のディフューズ色
		};

	public:
		IMeshSimple2D();
		virtual ~IMeshSimple2D();

		/// <summary>
		/// 初期化処理
		/// </summary>
		virtual void Init(ViewerCached _system) override = 0;
		/// <summary>
		/// 解放処理
		/// </summary>
		virtual void Release(ViewerCached _system) override = 0;
		/// <summary>
		/// 頂点構造体のサイズを取得する
		/// </summary>
		/// <returns>頂点構造体のサイズ(byte)</returns>
		virtual size_t GetVertexSize() const { return sizeof(Vertex); };
		/// <summary>
		/// インデクスの数を取得する
		/// </summary>
		/// <returns>インデックス数</returns>
		virtual uint32_t GetIndexCount() const = 0;
		/// <summary>
		/// 頂点数を取得する
		/// </summary>
		/// <returns>頂点数</returns>
		virtual uint32_t GetVertexCount() const = 0;

		/// <summary>
		/// テクスチャハンドルを取得する (任意)
		/// </summary>
		/// <returns>テクスチャがある場合ハンドル / なければ無効ハンドル</returns>
		virtual TextureHandle GetTextureHandle() const { return INVALID_HANDLE; }

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
