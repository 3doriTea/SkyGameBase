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
		/// ‰Šú‰»ˆ—
		/// </summary>
		void Init() override;
		/// <summary>
		/// ‰ğ•úˆ—
		/// </summary>
		void Release() override;
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
