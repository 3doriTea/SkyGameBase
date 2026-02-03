#pragma once
#include "pch/pch.h"
#include "Core/GameSystemViewer.h"


namespace wtgb
{
	/// <summary>
	/// シェーダのコンスタント
	/// </summary>
	template<typename StructT>
	class ShaderConstant
	{
		static_assert(alignof(StructT) == 16
			&& "コンスタントバッファの構造体はアラインメントが16byteである必要があります。");
	public:
		void Init(ViewerCached _system);
		void Send(ViewerCached _system);

	private:
		ComPtr<ID3D11Buffer> pConstantBuffer_;
	};
}

#include "ShaderConstant.inl"
