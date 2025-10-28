#pragma once
#include "pch/pch.h"
#include "GameComponent/Transform.h"

namespace wtgb
{
	class Fbx
	{
	public:
		Fbx();
		~Fbx();

		/// <summary>
		/// Fbxをロードする
		/// </summary>
		/// <param name="_fileName">ファイル名</param>
		/// <returns>Fbxをロードする</returns>
		HRESULT Load(const std::string& _fileName);
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
		int vertexCount_;  // 頂点数
		int polygonCount_;  // ポリゴン数
		int materialCount_;  // マテリアルの個数
	};
}
