#include "pch\pch.h"
#include "Direct3D.h"
#include "Direct3DResource.h"
#include "WTGBAssert.h"

using namespace wtgb;

namespace
{
	const Direct3DResource::Config D3D_RESOURCE_CONFIG
	{
	};
}

wtgb::Direct3D::Direct3D() :
	pResource_{ new Direct3DResource{ D3D_RESOURCE_CONFIG } }
{
}

wtgb::Direct3D::~Direct3D()
{
	SAFE_DELETE(pResource_);
}

wtgb::Result wtgb::Direct3D::Init(const ViewerInit& _viewer)
{
	wassert(pResource_ && "リソースのポインタが入ってない");

	if (pResource_ == nullptr)
	{
		return Result::Code::Failed;
	}

	pResource_->CallInit();

	HRESULT hResult{};

	D3D_FEATURE_LEVEL featureLevel{};

	hResult = D3D11CreateDevice(
		nullptr,                             // どのビデオアダプタを使用するか
		D3D_DRIVER_TYPE_HARDWARE,            // ドライバのタイプを渡す
		nullptr,                             // 上記をD3D_DRIVER_TYPE_SOFTWAREに設定しない限り nullptr
		D3D11_CREATE_DEVICE_DEBUG
		| D3D11_CREATE_DEVICE_BGRA_SUPPORT,  // デバッグモードを付けておく
		nullptr,                             // デバイス、コンテキストのレベル設定、 nullptrで勝手に配列を渡す
		0,                                   // 上記の引数でレベルを何要素指定したか
		D3D11_SDK_VERSION,                   // SDKのバージョン、必ずこの値に！
		pResource_->Device(),                // デバイスを指定
		&featureLevel,                       // 成功した場合サポートするバージョンを返す
		pResource_->Context());              // コンテキストを指定

	wassert(SUCCEEDED(hResult) && "D3D11CreateDeviceに失敗");
	if (FAILED(hResult))
	{
		return Result::Code::Failed;
	}

	return Result::Code::Ok;
}

void wtgb::Direct3D::Update(const ViewerUpdate& _system)
{
}

void wtgb::Direct3D::End()
{
	pResource_->CallRelease();
}
