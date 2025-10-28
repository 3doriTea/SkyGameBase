#include "pch\pch.h"
#include "Direct3D.h"
#include "Direct3D/Direct3DResource.h"
#include "WTGBAssert.h"

#include "GameSystem/GameWindow.h"

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

#pragma region D3D11デバイスの作成
	D3D_FEATURE_LEVEL featureLevel{};

	hResult = D3D11CreateDevice(
		nullptr,                                // どのビデオアダプタを使用するか
		D3D_DRIVER_TYPE_HARDWARE,               // ドライバのタイプを渡す
		nullptr,                                // 上記をD3D_DRIVER_TYPE_SOFTWAREに設定しない限り nullptr
		D3D11_CREATE_DEVICE_DEBUG
		| D3D11_CREATE_DEVICE_BGRA_SUPPORT,     // デバッグモードを付けておく
		nullptr,                                // デバイス、コンテキストのレベル設定、 nullptrで勝手に配列を渡す
		0,                                      // 上記の引数でレベルを何要素指定したか
		D3D11_SDK_VERSION,                      // SDKのバージョン、必ずこの値に！
		pResource_->Device().GetAddressOf(),    // デバイスを指定
		&featureLevel,                          // 成功した場合サポートするバージョンを返す
		pResource_->Context().GetAddressOf());  // コンテキストを指定

	wassert(SUCCEEDED(hResult) && "D3D11CreateDeviceに失敗");
	if (FAILED(hResult))
	{
		return Result::Code::Failed;
	}
#pragma endregion

#pragma region スワップチェーンの作成
	hResult = pResource_->Device().Get()->QueryInterface(
		__uuidof(IDXGIDevice),
		reinterpret_cast<void**>(pResource_->DXGIDevice().GetAddressOf()));
	wassert(SUCCEEDED(hResult) && "DXGIDeviceの作成に失敗");
	if (FAILED(hResult))
	{
		return Result::Code::Failed;
	}

	hResult = pResource_->DXGIDevice().Get()->GetAdapter(pResource_->DXGIAdapter().GetAddressOf());
	wassert(SUCCEEDED(hResult) && "DXGIAdapterの作成に失敗");
	if (FAILED(hResult))
	{
		return Result::Code::Failed;
	}

	hResult = pResource_->DXGIAdapter().Get()->GetParent(
		__uuidof(IDXGIFactory),
		reinterpret_cast<void**>(pResource_->DXGIFactory().GetAddressOf()));
	wassert(SUCCEEDED(hResult) && "DXGIFactoryの作成に失敗");
	if (FAILED(hResult))
	{
		return Result::Code::Failed;
	}

	const Vector2Int SCREEN_SIZE{ _viewer.Get<GameWindow>().GetMainWindowSize() };
	const GameWindow::RefreshRate SCREEN_REFRESH_RATE{ _viewer.Get<GameWindow>().GetMainWindowRefreshRate() };

	const DXGI_SWAP_CHAIN_DESC SWAP_CHAIN_DESC
	{
		.BufferDesc
		{
			.Width = static_cast<UINT>(SCREEN_SIZE.x),   // 描画領域の横幅
			.Height = static_cast<UINT>(SCREEN_SIZE.y),  // 描画領域の高さ
			.RefreshRate  // 画面を更新する間隔 (秒)
			{
				.Numerator = SCREEN_REFRESH_RATE.numerator,      // リフレッシュレートの分母
				.Denominator = SCREEN_REFRESH_RATE.denominator,  // リフレッシュレートの分子
			},
			.Format = DXGI_FORMAT_R8G8B8A8_UNORM,  // 何色使えるか
			.ScanlineOrdering = {},
			.Scaling = {}
		},
		.SampleDesc
		{
			.Count = 1,    // MSAA (アンチエイリアス) の設定
			.Quality = 0,  // 
		},
		.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,  // バックバッファの使い道は画面に描画すること
		.BufferCount = 1,  // バッファの枚数
		.OutputWindow = _viewer.Get<GameWindow>().GetMainWindowHandle(),
		.Windowed = _viewer.Get<GameWindow>().GetMainWindowIsWindowed(),
		.SwapEffect = {},
		.Flags = NULL,
	};

	hResult = pResource_->DXGIFactory().Get()->CreateSwapChain(
		pResource_->Device().Get(),
		const_cast<DXGI_SWAP_CHAIN_DESC*>(&SWAP_CHAIN_DESC),
		pResource_->SwapChain().GetAddressOf());
	wassert(SUCCEEDED(hResult) && "SwapChainの作成に失敗");
	if (FAILED(hResult))
	{
		return Result::Code::Failed;
	}
#pragma endregion

#pragma region レンダーターゲットビューの作成
	ID3D11Texture2D* pBackBuffer{ nullptr };


#pragma endregion

	return Result::Code::Ok;
}

void wtgb::Direct3D::Update(const ViewerUpdate& _system)
{
}

void wtgb::Direct3D::End()
{
	pResource_->CallRelease();
}
