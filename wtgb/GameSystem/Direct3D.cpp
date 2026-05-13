#include "pch\pch.h"
#include "Direct3D.h"
#include "Direct3D/Direct3DResource.h"
#include "WTGBAssert.h"

#include "GameSystem/GameWindow.h"
#include "GameSystem/ShaderCompile.h"

using namespace wtgb;

namespace
{
	const Direct3DResource::Config D3D_RESOURCE_CONFIG
	{
	};
}

wtgb::Direct3D::Direct3D() :
	pResource_{ std::make_unique<Direct3DResource>(D3D_RESOURCE_CONFIG) },
	resourceAccessor_{ this },
	system_{ nullptr },
	renderCallbacks_{},
	renderSkipperOnce_{ true }
{
}

wtgb::Direct3D::~Direct3D()
{
	//SAFE_DELETE(pResource_);
}

wtgb::Result wtgb::Direct3D::Init(const ViewerInit& _viewer)
{
	system_ = _viewer.GetCache();

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

#pragma region 深度バッファモードの作成

	{
		const D3D11_DEPTH_STENCIL_DESC DESC_BACK
		{
			.DepthEnable = TRUE,
			.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO,
			.DepthFunc = D3D11_COMPARISON_LESS_EQUAL,
			.StencilEnable = FALSE,
			.StencilReadMask = 0,
			.StencilWriteMask = 0,
			.FrontFace = {},
			.BackFace = {},
		};

		hResult = pResource_->Device().Get()->CreateDepthStencilState(
			&DESC_BACK,
			pResource_->DepthStencilAt(ZBufferMode::Back).GetAddressOf());
		wassert(SUCCEEDED(hResult) && "深度バッファモード-backの作成に失敗");
		if (FAILED(hResult))
		{
			return Result::Code::Failed;
		}
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
	//pResource_->Context().Get()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	pResource_->Context().Get()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	SetUseDepthBuffer(true);
	pResource_->Context().Get()->RSSetViewports(1, &viewport);
#pragma endregion

#pragma region ブレンドモードの作成

	const D3D11_RENDER_TARGET_BLEND_DESC RENDER_TARGET_BLEND_DESC_0
	{
		.BlendEnable = TRUE,
		.SrcBlend = D3D11_BLEND_SRC_ALPHA,
		.DestBlend = D3D11_BLEND_INV_SRC_ALPHA,
		.BlendOp = D3D11_BLEND_OP_ADD,
		.SrcBlendAlpha = D3D11_BLEND_ONE,
		.DestBlendAlpha = D3D11_BLEND_ZERO,
		.BlendOpAlpha = D3D11_BLEND_OP_ADD,
		.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL,
	};

	const D3D11_BLEND_DESC BLEND_DESC
	{
		.AlphaToCoverageEnable = FALSE,
		.IndependentBlendEnable = FALSE,
		.RenderTarget = { RENDER_TARGET_BLEND_DESC_0 },
	};
	hResult = pResource_->Device().Get()->CreateBlendState(&BLEND_DESC, pResource_->BlendStateAt(BlendMode::Alpha).GetAddressOf());

	wassert(SUCCEEDED(hResult) && "深度バッファ用バッファの作成に失敗");
	if (FAILED(hResult))
	{
		return Result::Code::Failed;
	}

	SetBlend(BlendMode::None);  // デフォルトの指定

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
	renderCallbacks_.clear();
}

void wtgb::Direct3D::Render()
{
	if (renderSkipperOnce_)
	{
		// ゲーム起動時の1フレームはちらつき防止のため捨てる
		renderSkipperOnce_ = false;
		return;
	}

	for (auto& callback : renderCallbacks_)
	{
		callback();  // 描画直前の処理
	}

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

void wtgb::Direct3D::SetShader(const ShaderHandle _hShader)
{
	ShaderCompile& shaderCompiler{ system_.Get<ShaderCompile>() };
	ID3D11DeviceContext* pContext{ pResource_->Context().Get() };

	pContext->VSSetShader(shaderCompiler.GetVertexShader(_hShader), nullptr, 0);
	pContext->PSSetShader(shaderCompiler.GetPixelShader(_hShader), nullptr, 0);
	pContext->IASetInputLayout(shaderCompiler.GetInputLayout(_hShader));
	pContext->RSSetState(shaderCompiler.GetRasterizerState(_hShader));
}

void wtgb::Direct3D::SetUseDepthBuffer(const bool _useDepthBuffer)
{
	// 深度バッファを使うならビューのポインタを取得、使わないなら nullptr
	ID3D11DepthStencilView* pDepthStencilView
	{
		_useDepthBuffer
		? pResource_->DepthStencilView().Get()
		: nullptr
	};
	pResource_->Context().Get()->OMSetRenderTargets(
		1,
		pResource_->RenderTargetView().GetAddressOf(),
		pDepthStencilView);
}

void wtgb::Direct3D::SetBlend(const BlendMode _mode)
{
	wassert(_mode != BlendMode::Max && "BlendModeにMaxは指定できない");
	switch (_mode)
	{
	case BlendMode::Alpha:
	{
		float blendFactor[]{ 1, 1, 1, 1 };

		// ブレンドモードをセットする
		pResource_->Context().Get()->OMSetBlendState(
			pResource_->BlendStateAt(_mode).Get(),
			blendFactor,
			Color::NONE);
		break;
	}
	case BlendMode::None:
	case BlendMode::Max:
		// ブレンドモードを特に指定しない
		pResource_->Context().Get()->OMSetBlendState(nullptr, nullptr, Color::NONE);
		break;
	default:
		wassert(false && "未実装のブレンドモード");
		break;
	}
}

void wtgb::Direct3D::SetZBuffer(const ZBufferMode _mode)
{
	wassert(_mode != ZBufferMode::Max && "ZBufferModeにMaxは指定できない");

	if (_mode == ZBufferMode::Max || _mode == ZBufferMode::None)
	{
		// ブレンドモードを特に指定しない
		pResource_->Context().Get()->OMSetDepthStencilState(nullptr, 0);
	}

	switch (_mode)
	{
	case ZBufferMode::Back:
		pResource_->Context().Get()->OMSetDepthStencilState(
			pResource_->DepthStencilAt(_mode).Get(), 0);
		break;
	case ZBufferMode::None:
		break;
	default:
		wassert(false && "未実装の深度バッファモード");
		break;
	}
}

void wtgb::Direct3D::AddRenderListener(const std::function<void()>& _callback)
{
	renderCallbacks_.push_back(_callback);
}

ID3D11Device* wtgb::Direct3D::ResourceAccessor::Device()
{
	return GetAccess()->pResource_->Device().Get();
}

ComPtr<ID3D11Device>& wtgb::Direct3D::ResourceAccessor::DeviceComPtr()
{
	return GetAccess()->pResource_->Device();
}

ID3D11DeviceContext* wtgb::Direct3D::ResourceAccessor::Context()
{
	return GetAccess()->pResource_->Context().Get();
}

ComPtr<ID3D11DeviceContext>& wtgb::Direct3D::ResourceAccessor::ContextComPtr()
{
	return GetAccess()->pResource_->Context();
}
