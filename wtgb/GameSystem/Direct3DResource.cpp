#include "pch\pch.h"
#include "Direct3DResource.h"

wtgb::Direct3DResource::Direct3DResource()
{
}

wtgb::Direct3DResource::~Direct3DResource()
{
}

void wtgb::Direct3DResource::Init()
{
}

void wtgb::Direct3DResource::Release()
{
	SAFE_RELEASE(pFactory_);
	SAFE_RELEASE(pAdapter_);
	SAFE_RELEASE(pDXGI_);

	SAFE_RELEASE(pContext_);
	SAFE_RELEASE(pDevice_);
}
