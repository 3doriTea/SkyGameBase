#pragma once
#include "pch/pch.h"
#include "../IResource.h"

namespace wtgb
{
	class Direct3DResource : public IResource
	{
	public:
		struct Config
		{
			
		};

	public:
		Direct3DResource(const Config& _config);
		~Direct3DResource();

		ComPtr<ID3D11Device>& Device() { return pDevice_; }
		ComPtr<ID3D11DeviceContext>& Context() { return pContext_; }

		ComPtr<IDXGIDevice1>& DXGIDevice() { return pDXGIDevice_; }
		ComPtr<IDXGIAdapter>& DXGIAdapter() { return pDXGIAdapter_; }
		ComPtr<IDXGIFactory>& DXGIFactory() { return pDXGIFactory_; }

		ComPtr<IDXGISwapChain>& SwapChain() { return pSwapChain_; }
		
		ComPtr<ID3D11RenderTargetView>& RenderTargetView() { return pRenderTargetView_; }
		ComPtr<ID3D11Texture2D>& DepthBuffer() { return pDepthBuffer_; }
		ComPtr<ID3D11DepthStencilView>& DepthStencilView() { return pDepthStencilView_; }

	private:
		/// <summary>
		/// 初期化処理
		/// </summary>
		void Init() override;

		/// <summary>
		/// 解放処理
		/// </summary>
		void Release() override;

	private:
		Config config_;  // 設定

		ComPtr<ID3D11Device> pDevice_;          // デバイス
		ComPtr<ID3D11DeviceContext> pContext_;  // デバイスコンテキスト

		ComPtr<IDXGIDevice1> pDXGIDevice_;   // 複数ディスプレイ制御 // TODO なぜDeviceとDevice1があるのかを調べる
		ComPtr<IDXGIAdapter> pDXGIAdapter_;  // 
		ComPtr<IDXGIFactory> pDXGIFactory_;  // 

		ComPtr<IDXGISwapChain> pSwapChain_;  // スワップチェーン

		ComPtr<ID3D11RenderTargetView> pRenderTargetView_;  // レンダーターゲットビュー
		ComPtr<ID3D11Texture2D> pDepthBuffer_;              // 深度バッファ
		ComPtr<ID3D11DepthStencilView> pDepthStencilView_;  // 深度ステンシルビュー
	};
}
