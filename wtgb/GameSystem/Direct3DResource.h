#pragma once
#include "pch/pch.h"
#include "IResource.h"

namespace wtgb
{
	class Direct3DResource : public IResource
	{
	public:
		Direct3DResource();
		~Direct3DResource();

		/// <summary>
		/// ‰Šú‰»ˆ—
		/// </summary>
		void Init() override;

		/// <summary>
		/// ‰ğ•úˆ—
		/// </summary>
		void Release() override;

	private:
		ID3D11Device* pDevice_;
		ID3D11DeviceContext* pContext_;

		IDXGIDevice1* pDXGI_; // TODO ‚È‚ºDevice‚ÆDevice1‚ª‚ ‚é‚Ì‚©‚ğ’²‚×‚é
		IDXGIAdapter* pAdapter_;
		IDXGIFactory* pFactory_;
	};
}
