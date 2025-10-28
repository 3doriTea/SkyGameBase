#include "pch/pch.h"
#include "InputResource.h"
#include "WTGBAssert.h"
#include "Utility/InitSequence.h"

wtgb::InputResource::InputResource(const Config& _config) :
	config_{ _config },
	pDirectInput_{ nullptr },
	pKeyDevice_{ nullptr },
	pMouseDevice_{ nullptr }
{
}

wtgb::InputResource::~InputResource()
{
}

void wtgb::InputResource::Init()
{
	HRESULT hResult{};
	hResult = InitSequence::Begin()
		.TryRun([this]() -> HRESULT
			{
				HRESULT hResult = DirectInput8Create(
					GetModuleHandle(nullptr),
					DIRECTINPUT_VERSION,
					IID_IDirectInput8,
					reinterpret_cast<VOID**>(&pDirectInput_),
					nullptr);
				wassert(SUCCEEDED(hResult) && "DirectInput8の作成に失敗");

				return hResult;
			})
		.TryRun([this]() -> HRESULT
			{
				HRESULT hResult = pDirectInput_->CreateDevice(GUID_SysKeyboard, &pKeyDevice_, nullptr);
				wassert(SUCCEEDED(hResult) && "キーボードデバイスの作成に失敗");
				hResult = pKeyDevice_->SetDataFormat(&c_dfDIKeyboard);
				wassert(SUCCEEDED(hResult) && "キーボードのフォーマット設定に失敗");
				hResult = pKeyDevice_->SetCooperativeLevel(config_.hWnd, config_.cooperativeLevelFlag);
				wassert(SUCCEEDED(hResult) && "キーボード干渉度合い設定に失敗");
				
				return hResult;
			})
		.TryRun([this]() -> HRESULT
			{
				HRESULT hResult = pDirectInput_->CreateDevice(GUID_SysMouse, &pMouseDevice_, nullptr);
				wassert(SUCCEEDED(hResult) && "マウスデバイスの作成に失敗");
				hResult = pMouseDevice_->SetDataFormat(&c_dfDIMouse);
				wassert(SUCCEEDED(hResult) && "マウスのフォーマット設定に失敗");
				hResult = pMouseDevice_->SetCooperativeLevel(config_.hWnd, config_.cooperativeLevelFlag);
				wassert(SUCCEEDED(hResult) && "マウス干渉度合い設定に失敗");
				
				return hResult;
			})
		.End();
}

void wtgb::InputResource::Release()
{
	SAFE_RELEASE(pMouseDevice_);
	SAFE_RELEASE(pKeyDevice_);
	SAFE_RELEASE(pDirectInput_);
}
