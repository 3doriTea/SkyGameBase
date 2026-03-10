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
				return DirectInput8Create(
					GetModuleHandle(nullptr),
					DIRECTINPUT_VERSION,
					IID_IDirectInput8,
					reinterpret_cast<VOID**>(&pDirectInput_),
					nullptr);
			}, "DirectInput8の作成に失敗")
		.TryRun([this]() -> HRESULT
			{
				return pDirectInput_->CreateDevice(GUID_SysKeyboard, &pKeyDevice_, nullptr);
			}, "キーボードデバイスの作成に失敗")
		.TryRun([this]() -> HRESULT
			{
				return pKeyDevice_->SetDataFormat(&c_dfDIKeyboard);
			}, "キーボードのフォーマット設定に失敗")
		.TryRun([this]() -> HRESULT
			{
				return pKeyDevice_->SetCooperativeLevel(config_.hWnd, config_.cooperativeLevelFlag);
			}, "キーボード干渉度合い設定に失敗")
		.TryRun([this]() -> HRESULT
			{
				return pDirectInput_->CreateDevice(GUID_SysMouse, &pMouseDevice_, nullptr);
			}, "マウスデバイスの作成に失敗")
		.TryRun([this]() -> HRESULT
			{
				return pMouseDevice_->SetDataFormat(&c_dfDIMouse);
			}, "マウスのフォーマット設定に失敗")
		.TryRun([this]() -> HRESULT
			{
				return pMouseDevice_->SetCooperativeLevel(config_.hWnd, config_.cooperativeLevelFlag);
			}, "マウス干渉度合い設定に失敗")
		.End();

	wassert(SUCCEEDED(hResult) && "InputResouce 初期化処理に失敗");
}

void wtgb::InputResource::Release()
{
	SAFE_RELEASE(pMouseDevice_);
	SAFE_RELEASE(pKeyDevice_);
	SAFE_RELEASE(pDirectInput_);
}
