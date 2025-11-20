#pragma once
#include <wtgb.h>
#include "GameSystem/ModelMesh/IMeshSimple.h"

using StagePoints = std::vector<Vector2>;

class StageMesh : public wtgb::IMeshSimple
{
public:
	/// <summary>
	/// 頂点情報
	/// </summary>
	struct Vertex
	{
		Vector4 position;
		Vector4 normal;
		Vector4 uv;
	};

	struct ConstantBuffer
	{
		Matrix4x4 matrixWVP;      // ワールドビュープロジェクションの合成行列
		Vector4 lightDirection;   // ライトの向き
		FLOAT ambientValue;       // 環境光の量
	};

public:
	StageMesh(ViewerCached _system, StagePoints& _points);
	~StageMesh();
	
	void Init() override;
	void Release() override;

	ComPtr<ID3D11Buffer>& GetVertexBuffer() override   { return pVertexBuffer_; }
	ComPtr<ID3D11Buffer>& GetIndexBuffer() override    { return pIndexBuffer_; }
	ComPtr<ID3D11Buffer>& GetConstantBuffer() override { return pConstantBuffer_; }
	/// <summary>
	/// 頂点のサイズを取得
	/// </summary>
	/// <returns>頂点の構造体サイズ(byte)</returns>
	size_t GetVertexSize() override { return sizeof(Vertex); }

private:
	/// <summary>
	/// <para>頂点のx"座標"の値をまとめてセットする</para>
	/// <para>position.xと uv.x　※法線のxは座標ではないため除く</para>
	/// </summary>
	/// <param name="_xValue">xの値</param>
	/// <param name="_vertex">セットしたい頂点</param>
	static void SetPosXValue(const float _xValue, Vertex* _vertex);

	ViewerCached& System() { return system_; }

private:
	StagePoints& points_;
	ViewerCached system_;

	ComPtr<ID3D11Buffer> pVertexBuffer_;    // 頂点バッファ
	ComPtr<ID3D11Buffer> pIndexBuffer_;    // インデックスバッファ
	ComPtr<ID3D11Buffer> pConstantBuffer_;  // コンスタントバッファ
};
