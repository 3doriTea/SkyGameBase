#pragma once
#include <wtgb.h>

using HeightPoints = std::vector<float>;

/// <summary>
/// 水面のメッシュ情報
/// </summary>
class WaterMesh : public wtgb::IMeshSimple
{
public:
	/// <summary>
	/// 水面メッシュ情報の設定
	/// </summary>
	struct Config
	{
		HeightPoints& points;            // 頂点たちの高さ情報参照
		const Vector2Int verticesCount;  // 頂点数
		const Vector2 verticesDistance;  // 頂点間の距離
	};

public:
	WaterMesh(Config& _config);
	~WaterMesh();

	void Init(ViewerCached _system) override;
	void Release(ViewerCached _system) override;

	ComPtr<ID3D11Buffer>& GetVertexBuffer() override { return pVertexBuffer_; }
	ComPtr<ID3D11Buffer>& GetIndexBuffer() override { return pIndexBuffer_; }
	ComPtr<ID3D11Buffer>& GetConstantBuffer() override { return pConstantBuffer_;}
	
	uint32_t GetIndexCount() const override { return indexCount_; }
	uint32_t GetVertexCount() const override { return vertexCount_; }

	void UpdateVertexBuffer(ViewerCached _system);

private:
	/// <summary>
	/// サイズ変更などで頂点をリセットする
	/// </summary>
	void ResetVertices();

private:
	const Vector2Int SIZE_;            // 頂点個数
	const Vector2 VERTICES_DISTANCE_;  // 頂点間の距離

	HeightPoints& points_;  // 波の頂点情報
	uint32_t vertexCount_;  // 頂点数
	uint32_t indexCount_;   // インデックス数

	ComPtr<ID3D11Buffer> pVertexBuffer_;    // 頂点バッファ
	ComPtr<ID3D11Buffer> pIndexBuffer_;     // インデックスバッファ
	ComPtr<ID3D11Buffer> pConstantBuffer_;  // コンスタントバッファ

	std::vector<Vertex> vertices_;  // 頂点情報
};
