#pragma once
#include "pch/pch.h"
#include "ModelResource.h"
#include "GameComponent/Transform.h"

namespace wtgb
{
	class Fbx : public ModelResource
	{
	public:
		/// <summary>
		/// 頂点
		/// </summary>
		struct Vertex
		{
			DirectX::XMVECTOR position;  // 座標
			DirectX::XMVECTOR normal;    // 法線
			DirectX::XMVECTOR uv;        // UV座標
		};

		/// <summary>
		/// 定数バッファ
		/// </summary>
		struct ConstantBuffer
		{
			//DirectX::XMMATRIX matWVP;
			//DirectX::XMMATRIX matNormal;
			//DirectX::XMFLOAT4 diffuse;
			//BOOL materialFLag;  // 16byte単位で送られるから仕方ない

			Matrix4x4 matrixProjection;   // Projection行列
			Matrix4x4 matrixView;         // View行列
			Matrix4x4 matrixWVP;          // ワールドビュープロジェクションの合成行列
			Matrix4x4 matrixUV;           // UV変換行列
			Matrix4x4 matrixRotateWorld;  // ワールド回転行列
			Vector4 lightDirection;       // ライトの向き
			Color lightColor;             // ライトの色
			Color diffuseColor;           // ディフューズカラー
			FLOAT ambientValue;           // 環境光の量
			BOOL hasTexture;              // テクスチャを持っているか
		};

		/// <summary>
		/// マテリアル情報
		/// </summary>
		struct Material
		{
			//fs::path textureFile;
			TextureHandle hTexture_;
			Color diffuse;
			ComPtr<ID3D11SamplerState> textureSamplerState;
		};

	public:
		using ModelResource::ModelResource;
		~Fbx();

		/// <summary>
		/// Fbxを描画する
		/// </summary>
		/// <param name="_transform">描画するモデルの座標系</param>
		void Draw(Transform& _transform);

		inline ComPtr<ID3D11Buffer>& GetVertexBuffer() { return pVertexBuffer_; }
		inline ComPtr<ID3D11Buffer>& GetIndexBufferAt(const size_t _index) { return pIndexBuffers_.at(_index); }
		inline ComPtr<ID3D11Buffer>& GetIndexBuffer() { return GetIndexBufferAt(0); }
		inline ComPtr<ID3D11Buffer>& GetConstantBuffer() { return pConstantBuffer_; }
		/// <summary>
		/// Fbxにアタッチされているマテリアル数を取得
		/// </summary>
		/// <returns>マテリアル数</returns>
		inline size_t GetMaterialCount() const { return materialCount_; }
		/// <summary>
		/// インデックス数を取得する
		/// </summary>
		/// <returns>インデックス数</returns>
		inline size_t GetIndexCountAt(const size_t _index) const { return indexCounts_.at(_index); }
		/// <summary>
		/// 頂点数を取得する
		/// </summary>
		/// <returns>頂点数</returns>
		inline uint32_t GetVertexCount() const override { return static_cast<uint32_t>(vertexCount_); }
		/// <summary>
		/// 複数あるマテリアルの1つを取得
		/// </summary>
		/// <param name="_index">インデックス</param>
		/// <returns>マテリアルの参照ポインタ</returns>
		inline Material& GetMaterialAt(const size_t _index) { return materials_.at(_index); }
		/// <summary>
		/// インデックス数を取得する
		/// </summary>
		/// <returns>インデックス数</returns>
		inline uint32_t GetIndexCount() const override { return static_cast<uint32_t>(GetIndexCountAt(0)); }

	private:
		/// <summary>
		/// Fbxをロードする
		/// </summary>
		void Init(ViewerCached _system) override;

		/// <summary>
		/// 読み込んだモデルの解放処理
		/// </summary>
		void Release(ViewerCached _system) override;

		void InitVertex(ViewerCached _system, FbxMesh* _pMesh);
		void InitIndex(ViewerCached _system, FbxMesh* _pMesh);
		void InitConstant(ViewerCached _system);
		void InitMaterial(ViewerCached _system, FbxNode* _pNode);

	private:
		fs::path modelFile_;  // ファイルパス

		size_t vertexCount_;               // 頂点数
		size_t polygonCount_;              // ポリゴン数
		size_t materialCount_;             // マテリアルの個数
		std::vector<size_t> indexCounts_;  // インデックス数

		ComPtr<ID3D11Buffer> pVertexBuffer_;               // 頂点バッファ
		std::vector<ComPtr<ID3D11Buffer>> pIndexBuffers_;  // インデックスバッファ
		ComPtr<ID3D11Buffer> pConstantBuffer_;             // コンスタントバッファ
		std::vector<Material> materials_;  // マテリアル情報
	};
}
