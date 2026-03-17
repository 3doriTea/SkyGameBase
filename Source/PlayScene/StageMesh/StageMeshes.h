#pragma once
#include <wtgb.h>
#include "GameSystem/ModelMesh/IMeshesSimple.h"

using StagePoints = std::vector<Vector2>;

/// <summary>
/// 坂ステージのメッシュ情報
/// </summary>
class StageMeshes : public wtgb::IMeshesSimple
{
	enum  // x-> ^z で面を見たときの各頂点
	{
		VERTEX_BOTTOM_LEFT,   // 左下 -x, -y
		VERTEX_BOTTOM_RIGHT,  // 右下 +x, -y
		VERTEX_TOP_LEFT,      // 左上 -x, +y
		VERTEX_TOP_RIGHT,     // 右上 +x, +y
		VERTEX_MAX,
	};

	using PlaneVertices = std::array<Vertex, VERTEX_MAX>;
public:
	StageMeshes(StagePoints& _points);
	~StageMeshes();

	void Init(ViewerCached _system) override;
	void Release(ViewerCached _system) override;

	ComPtr<ID3D11Buffer>& GetVertexBufferAt(const size_t _index) override { return pVertexBuffers_.at(_index); }
	ComPtr<ID3D11Buffer>& GetIndexBufferAt(const size_t _index) override { return pIndexBuffers_.at(_index); }
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
	uint32_t GetVertexCountAt(const size_t _index) const override { return vertexCounts_.at(_index); }

	/// <summary>
	/// インデックス数を取得する
	/// </summary>
	/// <returns>インデックス数</returns>
	uint32_t GetIndexCountAt(const size_t _index) const override { return indexCounts_.at(_index); }

	/// <summary>
	/// テクスチャハンドルを取得する
	/// </summary>
	/// <returns></returns>
	TextureHandle GetTextureHandleAt(const size_t _index) const override { return hTextures_.at(_index); }

	/// <summary>
	/// 描画する面の数
	/// </summary>
	/// <returns></returns>
	size_t GetPlaneCount() const override { return pVertexBuffers_.size(); }

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

	std::vector<uint32_t> vertexCounts_;
	std::vector<uint32_t> indexCounts_;

	std::vector<TextureHandle> hTextures_;  // テクスチャのハンドル

	std::vector<ComPtr<ID3D11Buffer>> pVertexBuffers_;    // 頂点バッファ
	std::vector<ComPtr<ID3D11Buffer>> pIndexBuffers_;     // インデックスバッファ
	ComPtr<ID3D11Buffer> pConstantBuffer_;  // コンスタントバッファ
};
