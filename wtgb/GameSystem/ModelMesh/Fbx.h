#pragma once
#include "pch/pch.h"
#include "IModel.h"
#include "GameComponent/Transform.h"

namespace wtgb
{
	class Fbx : public IModel
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

	public:
		Fbx();
		~Fbx();

		/// <summary>
		/// Fbxをロードする
		/// </summary>
		/// <param name="_fileName">ファイル名</param>
		/// <returns>Fbxをロードする</returns>
		HRESULT TryLoad(const std::string& _fileName);
		/// <summary>
		/// Fbxを描画する
		/// </summary>
		/// <param name="_transform">描画するモデルの座標系</param>
		void Draw(Transform& _transform);
		/// <summary>
		/// 読み込んだモデルの解放処理
		/// </summary>
		void Release();

	private:
		void InitVertex(ufbx_mesh* pMesh, ufbx_mesh_part* pPart);

	private:
		int vertexCount_;  // 頂点数
		int polygonCount_;  // ポリゴン数
		int materialCount_;  // マテリアルの個数
	};
}
