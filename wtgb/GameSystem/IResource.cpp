#include "pch\pch.h"
#include "IResource.h"
#include "WTGBAssert.h"

wtgb::IResource::IResource()
{
#ifdef _DEBUG
	isReleased_ = true;
#endif
}

wtgb::IResource::~IResource()
{
	wassert(isReleased_ && "リソースを解放せずにデストラクタが呼ばれている");
}

void wtgb::IResource::CallInit()
{
	isReleased_ = false;
	CallInit();
}

void wtgb::IResource::CallRelease()
{
	Release();
	isReleased_ = true;
}
