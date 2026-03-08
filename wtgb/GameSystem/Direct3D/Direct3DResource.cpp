#include "pch\pch.h"
#include "Direct3DResource.h"

wtgb::Direct3DResource::Direct3DResource(const Config& _config) :
	config_{ _config },
	pDevice_{ nullptr },
	pContext_{ nullptr }/*,
	pDXGI_{ nullptr },
	pAdapter_{ nullptr },
	pFactory_{ nullptr }*/
{
}

wtgb::Direct3DResource::~Direct3DResource()
{
}

ComPtr<ID3D11BlendState>& wtgb::Direct3DResource::BlendStateAt(const BlendMode _blendMode)
{
	return pBlendStates_.at(static_cast<size_t>(_blendMode));
}

ComPtr<ID3D11DepthStencilState>& wtgb::Direct3DResource::DepthStencilAt(const ZBufferMode _zbufferMode)
{
	return pDepthStencilStates_.at(static_cast<size_t>(_zbufferMode));
}

void wtgb::Direct3DResource::Init()
{
	// pDevice_->QueryInterface(__uuidof(IDXGIDevice1), reinterpret_cast<void**>(&pDXGI_));
	// pDXGI_->GetAdapter(&pAdapter_);
	// pAdapter_->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory_));
}

void wtgb::Direct3DResource::Release()
{
	pRenderTargetView_.Reset();
	pDepthStencilView_.Reset();
	pDepthBuffer_.Reset();

	for (auto& pBlendState : pBlendStates_)
	{
		pBlendState.Reset();
	}
	for (auto& pDepthStencilState : pDepthStencilStates_)
	{
		pDepthStencilState.Reset();
	}

	pSwapChain_.Reset();


	pDXGIDevice_.Reset();
	pDXGIAdapter_.Reset();
	pDXGIFactory_.Reset();

	if (pContext_)
	{
		pContext_->ClearState();
		pContext_->Flush();
	}

	pContext_.Reset();
	pDevice_.Reset();
}
