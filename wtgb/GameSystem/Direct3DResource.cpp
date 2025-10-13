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

void wtgb::Direct3DResource::Init()
{
	// pDevice_->QueryInterface(__uuidof(IDXGIDevice1), reinterpret_cast<void**>(&pDXGI_));
	// pDXGI_->GetAdapter(&pAdapter_);
	// pAdapter_->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory_));
}

void wtgb::Direct3DResource::Release()
{
	/*SAFE_RELEASE(pFactory_);
	SAFE_RELEASE(pAdapter_);
	SAFE_RELEASE(pDXGI_);*/

	SAFE_RELEASE(pContext_);
	SAFE_RELEASE(pDevice_);
}
