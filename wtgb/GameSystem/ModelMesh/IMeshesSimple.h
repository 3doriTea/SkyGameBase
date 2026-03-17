#pragma once
#include "Utility/IResource.h"
#include "Core/GameSystemViewer.h"

namespace wtgb
{
	class IMeshesSimple : public IResource<ViewerCached>
	{
	public:
		/// <summary>
		/// 頂点情報
		/// </summary>
		struct Vertex
		{
			Vector4 position;  // 頂点座標
			Vector4 normal;    // 法線
			Vector4 uv;        // UV座標
		};

		/// <summary>
		/// コンスタントバッファ
		/// </summary>
		struct alignas(16) ConstantBuffer
		{
			Matrix4x4 matrixProjection;   // Projection行列
			Matrix4x4 matrixView;         // View行列
			Matrix4x4 matrixWVP;          // ワールドビュープロジェクションの合成行列
			Matrix4x4 matrixUV;           // UV変換行列
			Matrix4x4 matrixRotateWorld;  // 法線用ワールド回転行列
			Vector4 lightDirection;       // 平行光線の向き
			Color lightColor;             // 平行光線の色
			Color diffuseColor;           // テクスチャが無い場合のディフューズ色
			FLOAT ambientValue;           // 環境光の量
			BOOL hasTexture;              // テクスチャを持っているか
		};

	public:
		IMeshesSimple();
		virtual ~IMeshesSimple();

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
		/// <param name="_at">アクセスするインデクス</param>
		/// <returns>インデックス数</returns>
		virtual uint32_t GetIndexCountAt(const size_t _index) const = 0;
		/// <summary>
		/// 頂点数を取得する
		/// </summary>
		/// <param name="_at">アクセスするインデクス</param>
		/// <returns>頂点数</returns>
		virtual uint32_t GetVertexCountAt(const size_t _index) const = 0;

		/// <summary>
		/// テクスチャハンドルを取得する (任意)
		/// </summary>
		/// <param name="_at">アクセスするインデクス</param>
		/// <returns>テクスチャがある場合ハンドル / なければ無効ハンドル</returns>
		virtual TextureHandle GetTextureHandleAt(const size_t _index) const { return INVALID_HANDLE; }

		/// <summary>
		/// 頂点バッファを取得する
		/// </summary>
		/// <param name="_at">アクセスするインデクス</param>
		/// <returns>頂点バッファ</returns>
		virtual ComPtr<ID3D11Buffer>& GetVertexBufferAt(const size_t _index) = 0;
		/// <summary>
		/// インデックスバッファを取得する
		/// </summary>
		/// <param name="_at">アクセスするインデクス</param>
		/// <returns>インデックスバッファ</returns>
		virtual ComPtr<ID3D11Buffer>& GetIndexBufferAt(const size_t _index) = 0;
		/// <summary>
		/// コンスタントバッファを取得する
		/// </summary>
		/// <returns>コンスタントバッファ</returns>
		virtual ComPtr<ID3D11Buffer>& GetConstantBuffer() = 0;

		/// <summary>
		/// 描画する面の数
		/// </summary>
		/// <returns></returns>
		virtual size_t GetPlaneCount() const = 0;
	};
}
