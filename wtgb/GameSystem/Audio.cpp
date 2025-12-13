#include "pch\pch.h"
#include "Audio.h"
#include "WTGBAssert.h"

wtgb::Audio::Audio()
{
}

wtgb::Audio::~Audio()
{
}

wtgb::Result wtgb::Audio::Init(const ViewerInit& _viewer)
{
	HRESULT hResult{};

	hResult = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	wassert(SUCCEEDED(hResult) && "COMÇÃèâä˙âªÇ…é∏îs");
	if (FAILED(hResult))
	{
		return Result::Code::Failed;
	}

	hResult = XAudio2Create();
	wassert(SUCCEEDED(hResult) && "COMÇÃèâä˙âªÇ…é∏îs");
	if (FAILED(hResult))
	{
		return Result::Code::Failed;
	}

	return Result();
}
