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

		/// <summary>
		/// Direct3Dデバイスを取得
		/// </summary>
		/// <returns>Direct3Dデバイス</returns>
		ID3D11Device** Device() { return &pDevice_; }
		/// <summary>
		/// デバイスコンテキストを取得
		/// </summary>
		/// <returns>Direct3Dのデバイスコンテキスト</returns>
		ID3D11DeviceContext** Context() { return &pContext_; }

		/// <summary>
		/// DXGIデバイスを取得
		/// </summary>
		/// <returns>DXGIデバイス</returns>
		IDXGIDevice** DXGIDevice() { return &pDXGIDevice_; }
		/// <summary>
		/// DXGIファクトリを取得
		/// </summary>
		/// <returns>DXGIファクトリを取得</returns>
		IDXGIFactory2** DXGIFactory() { return &pDXGIFactory_; }
		/// <summary>
		/// DXGIアダプタを取得
		/// </summary>
		/// <returns>DXGIアダプタを取得</returns>
		IDXGIAdapter1** DXGIAdapter() { return &pDXGIAdapter_; }

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

		ID3D11Device* pDevice_;          // Direct3D デバイス
		ID3D11DeviceContext* pContext_;  // Direct3D デバイスコンテキスト

		// TODO: GPUごとに ...
		IDXGIDevice* pDXGIDevice_;     // DXGI デバイス

		IDXGIFactory2* pDXGIFactory_;  // DXGI ファクトリ
		
		// TODO: モニターごとに...
		IDXGIAdapter1* pDXGIAdapter_;  // DXGI アダプタ

		// 

		//IDXGIDevice1* pDXGI_;     // 複数ディスプレイ制御 // TODO なぜDeviceとDevice1があるのかを調べる
		//IDXGIAdapter* pAdapter_;  // 
		//IDXGIFactory* pFactory_;  // 
	};
}
