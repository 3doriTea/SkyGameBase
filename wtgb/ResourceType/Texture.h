#pragma once
#include "pch/pch.h"
#include "Utility/IResource.h"

namespace wtgb
{
	class Texture : public IResource
	{
	public:
		Texture();
		~Texture();
		
		bool TryLoad(const std::string& _fileName);

	private:
		ComPtr<ID3D11SamplerState> pSampler_;  // サンプラーステート
		ComPtr<ID3D11ShaderResourceView> p
	};
}
