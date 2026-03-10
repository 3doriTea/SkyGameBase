#pragma once
#include <wtgb.h>
#include "GameSystem/ModelMesh/IMeshSimple.h"

class TestBillBoard : wtgb::GameObject
{
public:
	class BillBoard : public wtgb::IMeshSimple
	{
	public:
		BillBoard(ViewerCached _system);
		~BillBoard();

		void Init(ViewerCached _system) override;
		void Release(ViewerCached _system) override;

		ComPtr<ID3D11Buffer>& GetVertexBuffer() override { return pVertexBuffer_; }
		ComPtr<ID3D11Buffer>& GetIndexBuffer() override { return pIndexBuffer_; }
		ComPtr<ID3D11Buffer>& GetConstantBuffer() override { return pConstantBuffer_; }
		uint32_t GetVertexCount() const override { return vertexCount_; }
		uint32_t GetIndexCount() const override { return indexCount_; }


	private:
		ViewerCached& System() { return system_; }

	private:
		ViewerCached system_;

		uint32_t vertexCount_;
		uint32_t indexCount_;

		ComPtr<ID3D11Buffer> pVertexBuffer_;    // 頂点バッファ
		ComPtr<ID3D11Buffer> pIndexBuffer_;    // インデックスバッファ
		ComPtr<ID3D11Buffer> pConstantBuffer_;  // コンスタントバッファ
	};

public:
	TestBillBoard();
	~TestBillBoard();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	BillBoard billBoard_;
};
