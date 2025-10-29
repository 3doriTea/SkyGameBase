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
	// 描画するバックバッファを一時的に取得
	ComPtr<ID3D11Texture2D> pBackBuffer{ nullptr };
	hResult = pResource_->SwapChain().Get()->GetBuffer(
		0,
		__uuidof(ID3D11Texture2D),
		reinterpret_cast<void**>(pBackBuffer.GetAddressOf()));
	wassert(SUCCEEDED(hResult) && "バックバッファの取得に失敗");
	if (FAILED(hResult))
	{
		return Result::Code::Failed;
	}

	// レンダーターゲットビューを作成
	hResult = pResource_->Device().Get()->CreateRenderTargetView(
		pBackBuffer.Get(),
		nullptr,
		pResource_->RenderTargetView().GetAddressOf());
	wassert(SUCCEEDED(hResult) && "レンダーターゲットビューの作成に失敗");
	if (FAILED(hResult))
	{
		return Result::Code::Failed;
	}

	// 一時的に取得したバックバッファを明示的に解放
	pBackBuffer.Reset();
#pragma endregion

#pragma region 深度ステンシルビュー(深度バッファ)の作成
	//TODO: const Vector2Int SCREEN_SIZE{ _viewer.Get<GameWindow>().GetMainWindowSize() };

	const D3D11_TEXTURE2D_DESC DEPTH_BUFFER_DESC
	{
		.Width = static_cast<UINT>(SCREEN_SIZE.x),   // 横幅
		.Height = static_cast<UINT>(SCREEN_SIZE.y),  // 高さ
		.MipLevels = 1,                              // テクスチャ内のミップマップレベル (ここでは関係無い?)
		.ArraySize = 1,                              // テクスチャ内の配列サイズ (ここでは関係無い?)
		.Format = DXGI_FORMAT_D32_FLOAT,             // テクスチャの形式
		.SampleDesc
		{
			.Count = 1,    // MSAA (アンチエイリアス) の設定
			.Quality = 0,  // 
		},
		.Usage = D3D11_USAGE_DEFAULT,           // 読み書きの識別
		.BindFlags = D3D11_BIND_DEPTH_STENCIL,  // 深度ステンシルとして使う！
		.CPUAccessFlags = 0,                    // CPUアクセスの種類
		.MiscFlags = 0,                         // その他フラグ
	};

	hResult = pResource_->Device().Get()->CreateTexture2D(
		&DEPTH_BUFFER_DESC,
		nullptr,
		pResource_->DepthBuffer().GetAddressOf());
	wassert(SUCCEEDED(hResult) && "深度バッファ用バッファの作成に失敗");
	if (FAILED(hResult))
	{
		return Result::Code::Failed;
	}

	hResult = pResource_->Device().Get()->CreateDepthStencilView(
		pResource_->DepthBuffer().Get(),
		nullptr,
		pResource_->DepthStencilView().GetAddressOf());
	wassert(SUCCEEDED(hResult) && "深度ステンシルビューの作成に失敗");
	if (FAILED(hResult))
	{
		return Result::Code::Failed;
	}
#pragma endregion

#pragma region ビューポート (描画範囲) 設定
	// ビューポートの情報
	D3D11_VIEWPORT viewport
	{
		.TopLeftX = 0,                                // 左端
		.TopLeftY = 0,                                // 上端
		.Width = static_cast<float>(SCREEN_SIZE.x),   // 横幅
		.Height = static_cast<float>(SCREEN_SIZE.y),  // 高さ
		.MinDepth = 0.0f,                             // 手前
		.MaxDepth = 1.0f,                             // 奥
	};

	// データを画面に描画するための一通りの設定 (パイプライン)
	pResource_->Context().Get()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pResource_->Context().Get()->OMSetRenderTargets(
		1,
		pResource_->RenderTargetView().GetAddressOf(),
		pResource_->DepthStencilView().Get());
	pResource_->Context().Get()->RSSetViewports(1, &viewport);
#pragma endregion
	return Result::Code::Ok;
}

void wtgb::Direct3D::Update(const ViewerUpdate& _system)
{
	float backgroundColor[4]{ 0.0f, 1.0f, 1.0f, 1.0f };
	// 画面クリア
	pResource_->Context().Get()->ClearRenderTargetView(
		pResource_->RenderTargetView().Get(),
		backgroundColor);
	// 深度バッファ
	pResource_->Context().Get()->ClearDepthStencilView(
		pResource_->DepthStencilView().Get(),
		D3D11_CLEAR_DEPTH,  // 深度をクリアする
		1.0f,
		0);
}

void wtgb::Direct3D::End()
{
	pResource_->CallRelease();
}

void wtgb::Direct3D::Render()
{
	// バックバッファと反転して描画
	HRESULT hResult{ pResource_->SwapChain().Get()->Present(0, 0) };
	static const int ERROR_TOLERANCE_COUNT{ 3 };
	static int swapMissCount{ 0 };
	if (FAILED(hResult))
	{
		swapMissCount++;
		wassert(swapMissCount > ERROR_TOLERANCE_COUNT
			&& "スワップチェーンのスワップに失敗");

		Game::Exit();
	}
}
