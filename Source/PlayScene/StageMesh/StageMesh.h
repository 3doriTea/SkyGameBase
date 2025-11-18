#pragma once
#include <wtgb.h>
#include "pch/pch.h"
#include "Utility/IResource.h"

class StageMesh : public wtgb::IResource
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
	StageMesh();
	~StageMesh();
	
	void Init() override;
	void Release() override;

private:
	ComPtr<ID3D11Buffer> pVertexBuffer_;    // 頂点バッファ
	ComPtr<ID3D11Buffer> pIndexBuffers_;    // インデックスバッファ
	ComPtr<ID3D11Buffer> pConstantBuffer_;  // コンスタントバッファ
};
