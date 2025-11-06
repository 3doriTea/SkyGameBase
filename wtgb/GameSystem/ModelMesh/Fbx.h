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
			Vector3 position;  // 座標
			Vector3 normal;    // 法線
			Vector2 uv;        // UV座標
		};

		/// <summary>
		/// 定数バッファ
		/// </summary>
		struct ConstantBuffer
		{
			DirectX::XMMATRIX matWVP;
			DirectX::XMMATRIX matNormal;
			DirectX::XMFLOAT4 diffuse;
			BOOL materialFLag;  // 16byte単位で送られるから仕方ない
		};

		/// <summary>
		/// マテリアル情報
		/// </summary>
		struct Material
		{
			std::string textureFile;

		};

	public:
		using ModelResource::ModelResource;
		~Fbx();

		/// <summary>
		/// Fbxを描画する
		/// </summary>
		/// <param name="_transform">描画するモデルの座標系</param>
		void Draw(Transform& _transform);

		ComPtr<ID3D11Buffer>& GetVertexBuffer() { return pVertexBuffer_; }
		ComPtr<ID3D11Buffer>& GetIndexBuffer() { return pIndexBuffer_; }
		ComPtr<ID3D11Buffer>& GetConstantBuffer() { return pConstantBuffer_; }
		/// <summary>
		/// Fbxにアタッチされているマテリアル数を取得
		/// </summary>
		/// <returns>マテリアル数</returns>
		size_t GetMaterialCount() const { return materialCount_; }
		/// <summary>
		/// インデックス数を取得する
		/// </summary>
		/// <returns>インデックス数</returns>
		size_t GetIndexCount() const { return indexCount_; }

	private:
		/// <summary>
		/// Fbxをロードする
		/// </summary>
		void Init() override;

		/// <summary>
		/// 読み込んだモデルの解放処理
		/// </summary>
		void Release() override;

		void InitVertex(FbxMesh* _pMesh);
		void InitIndex(FbxMesh* _pMesh);
		void InitConstant();
		void InitMaterial(FbxNode* _pNode);

	private:
		size_t vertexCount_;               // 頂点数
		size_t polygonCount_;              // ポリゴン数
		size_t materialCount_;             // マテリアルの個数
		std::vector<size_t> indexCounts_;  // インデックス数

		ComPtr<ID3D11Buffer> pVertexBuffer_;               // 頂点バッファ
		std::vector<ComPtr<ID3D11Buffer>> pIndexBuffers_;  // インデックスバッファ
		ComPtr<ID3D11Buffer> pConstantBuffer_;             // コンスタントバッファ
		std::vector<Material> materials_;                  // マテリアル情報
	};
}
