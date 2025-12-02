#pragma once
#include <wtgb.h>

using WavePoints = std::vector<float>;

/// <summary>
/// 水面のメッシュ情報
/// </summary>
class WaterMesh : public wtgb::IMeshSimple
{
public:
	WaterMesh(ViewerCached _system, WavePoints& _points, const Vector2Int _size);
	~WaterMesh();

	void Init() override;
	void Release() override;

	ComPtr<ID3D11Buffer>& GetVertexBuffer() override { return pVertexBuffer_; }
	ComPtr<ID3D11Buffer>& GetIndexBuffer() override { return pIndexBuffer_; }
	ComPtr<ID3D11Buffer>& GetConstantBuffer() override { return pConstantBuffer_;}
	
	uint32_t GetIndexCount() const override { return indexCount_; }
	uint32_t GetVertexCount() const override { return vertexCount_; }

private:
	/// <summary>
	/// 波の頂点情報を更新する
	/// </summary>
	void UpdateWaveVertex();

private:
	const Vector2Int SIZE_;  // 頂点個数

	WavePoints& points_;  // 波の頂点情報
	ViewerCached system_;  // システムアクセス用

	uint32_t vertexCount_;  // 頂点数
	uint32_t indexCount_;  // インデックス数

	ComPtr<ID3D11Buffer> pVertexBuffer_;    // 頂点バッファ
	ComPtr<ID3D11Buffer> pIndexBuffer_;     // インデックスバッファ
	ComPtr<ID3D11Buffer> pConstantBuffer_;  // コンスタントバッファ

	std::vector<Vertex> vertices;  // 頂点情報
};
