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

	public:
		using ModelResource::ModelResource;
		~Fbx();

		/// <summary>
		/// Fbxを描画する
		/// </summary>
		/// <param name="_transform">描画するモデルの座標系</param>
		void Draw(Transform& _transform);

	private:
		/// <summary>
		/// Fbxをロードする
		/// </summary>
		void Init() override;

		/// <summary>
		/// 読み込んだモデルの解放処理
		/// </summary>
		void Release() override;

		void InitTest(ufbx_mesh* pMesh);

		void InitVertex(ufbx_mesh* pMesh, ufbx_mesh_part* pPart);
		void InitIndex(ufbx_mesh* pMesh);
		void InitConstant();

	private:
		size_t vertexCount_;  // 頂点数
		size_t polygonCount_;  // ポリゴン数
		size_t materialCount_;  // マテリアルの個数

		ComPtr<ID3D11Buffer> pVertexBuffer_;    // 頂点バッファ
		ComPtr<ID3D11Buffer> pIndexBuffer_;     // いんでっくすバッファ
		ComPtr<ID3D11Buffer> pConstantBuffer_;  // コンスタントバッファ

	};
}
