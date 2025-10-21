#include "pch\pch.h"
#include "Direct3D.h"
#include "Direct3D/Direct3DResource.h"
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

	// TODO: モニターとGPUの関係を理解する必要がある
	// DXGI_OUTPUT_DESC 
	// TODO: モニター解像度が違うから、swapchainから作られたdirectxのオブジェクトは作り直し
	// => 将来的Direct2Dも作り直し
	hResult = D3D11CreateDevice(
		// TODO: ここで指定するデバイスは一つ、だからデバイスが複数必要？
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

	//pResource_-

	/*IDXGIFactory2::CreateSwapChainForHwnd(
		pResource_->DXGIFactory(),
		pResource_->Device(),
		)*/

	return Result::Code::Ok;
}

void wtgb::Direct3D::Update(const ViewerUpdate& _system)
{
}

void wtgb::Direct3D::End()
{
	// TODO: フルスクリーンだと解放できないから SwapChainのSetFullScreen

	// MEMO: アダプタがモニターを列挙、IDXGIOutput
	// EnumOutputs でモニター列挙、IDXGIOutputがGPU
	// NVIDIAのGPU(=アダプタ)から列挙すると、モニターサブ
	// 内臓GPU(=アダプタ)から列挙すると、モニターメイン
	pResource_->CallRelease();
}
