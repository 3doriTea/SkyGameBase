#pragma once
#include <wtgb.h>
#include "GameSystem/ModelMesh/IMeshSimple.h"

using StagePoints = std::vector<Vector2>;

/// <summary>
/// 坂ステージのメッシュ情報
/// </summary>
class StageMesh : public wtgb::IMeshSimple
{
public:
	StageMesh(StagePoints& _points, float& _textureScale);
	~StageMesh();
	
	void Init(ViewerCached _system) override;
	void Release(ViewerCached _system) override;

	ComPtr<ID3D11Buffer>& GetVertexBuffer() override   { return pVertexBuffer_; }
	ComPtr<ID3D11Buffer>& GetIndexBuffer() override    { return pIndexBuffer_; }
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
	/// <summary>
	/// <para>頂点のx"座標"の値をまとめてセットする</para>
	/// <para>position.xと uv.x　※法線のxは座標ではないため除く</para>
	/// </summary>
	/// <param name="_xValue">xの値</param>
	/// <param name="_vertex">セットしたい頂点</param>
	static void SetPosXValue(const float _xValue, Vertex* _vertex);

	void GenerateVertices(ViewerCached _system);
	void GenerateIndices(ViewerCached _system);
	void GenerateConstant(ViewerCached _system);

private:
	StagePoints& points_;
	float& textureScale_;  // テクスチャの拡縮

	uint32_t vertexCount_;
	uint32_t indexCount_;

	TextureHandle hTexture_;  // テクスチャのハンドル

	ComPtr<ID3D11Buffer> pVertexBuffer_;    // 頂点バッファ
	ComPtr<ID3D11Buffer> pIndexBuffer_;     // インデックスバッファ
	ComPtr<ID3D11Buffer> pConstantBuffer_;  // コンスタントバッファ
};
