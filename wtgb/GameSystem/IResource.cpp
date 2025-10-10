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

#ifdef _DEBUG
	isReleased_ = false;
#endif
	CallInit();
}

void wtgb::IResource::CallRelease()
{
	Release();
#ifdef _DEBUG
	isReleased_ = true;
#endif
}
