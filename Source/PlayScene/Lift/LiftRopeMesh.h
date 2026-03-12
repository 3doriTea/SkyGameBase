#pragma once
#include <wtgb.h>

using RopePoints = std::vector<Vector2>;

/// <summary>
/// ロープのメッシュ部分
/// </summary>
class LiftRopeMesh : public wtgb::IMeshSimple
{
public:
	/// <summary>
	/// ロームのメッシュ部分の設定
	/// </summary>
	struct Config
	{
		Config(
			float _offsetX,
			float _widthX,
			RopePoints& _points) :
			offsetX{ _offsetX },
			widthX{ _widthX },
			points{ _points }
		{
		}
		float offsetX;       // x軸の開始位置
		float widthX;        // x軸の幅
		RopePoints& points;  // yz平面で見たときの各頂点
	};

public:
	LiftRopeMesh(Config&& _config);
	~LiftRopeMesh();

	void Init(ViewerCached _system) override;
	void Release(ViewerCached _system) override;

	ComPtr<ID3D11Buffer>& GetVertexBuffer() override { return pVertexBuffer_; }
	ComPtr<ID3D11Buffer>& GetIndexBuffer() override { return pIndexBuffer_; }
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
	Config config_;  // 設定

	uint32_t vertexCount_;
	uint32_t indexCount_;

	TextureHandle hTexture_;  // テクスチャのハンドル

	ComPtr<ID3D11Buffer> pVertexBuffer_;    // 頂点バッファ
	ComPtr<ID3D11Buffer> pIndexBuffer_;     // インデックスバッファ
	ComPtr<ID3D11Buffer> pConstantBuffer_;  // コンスタントバッファ
};
