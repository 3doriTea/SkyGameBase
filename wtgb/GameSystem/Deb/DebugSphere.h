#pragma once
#include "GameSystem/ModelMesh/IMeshSimple.h"

namespace wtgb
{
	class DebugSphere : public IMeshSimple
	{
	public:
		DebugSphere();
		~DebugSphere();

		/// <summary>
		/// 初期化処理
		/// </summary>
		void Init(ViewerCached _system) override;
		/// <summary>
		/// 解放処理
		/// </summary>
		void Release(ViewerCached _system) override;
		uint32_t GetIndexCount() const override;
		uint32_t GetVertexCount() const override;
		inline ComPtr<ID3D11Buffer>& GetVertexBuffer() override { return pVertexBuffer_; }
		inline ComPtr<ID3D11Buffer>& GetIndexBuffer() override { return pIndexBuffer_; }
		inline ComPtr<ID3D11Buffer>& GetConstantBuffer() override { return pConstantBuffer_; }

	private:
		uint32_t indexCount_;
		uint32_t vertexCount_;

		ComPtr<ID3D11Buffer>& pVertexBuffer_;
		ComPtr<ID3D11Buffer>& pIndexBuffer_;
		ComPtr<ID3D11Buffer>& pConstantBuffer_;
	};
}
