#include "pch\pch.h"
#include "InputResource.h"
#include "WTGBAssert.h"

wtgb::InputResource::InputResource()
{
}

wtgb::InputResource::~InputResource()
{
}

void wtgb::InputResource::Init()
{
	HRESULT hResult{};
	
	hResult = DirectInput8Create(
		GetModuleHandle(nullptr),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		reinterpret_cast<VOID**>(&pDirectInput_),
		nullptr);
	wassert(SUCCEEDED(hResult) && "Directinput8の作成に失敗");

	hResult = pDirectInput_->CreateDevice(GUID_SysKeyboard, &pKeyDevice_, nullptr);
	wassert(SUCCEEDED(hResult) && "キーボードデバイスの作成に失敗");

	hResult = pDirectInput_->CreateDevice(GUID_SysMouse, &pMouseDevice_, nullptr);
	wassert(SUCCEEDED(hResult) && "マウスデバイスの作成に失敗");

}

void wtgb::InputResource::Release()
{
}
