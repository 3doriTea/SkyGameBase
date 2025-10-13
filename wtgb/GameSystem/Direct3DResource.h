#pragma once
#include "pch/pch.h"
#include "IResource.h"

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

		ID3D11Device** Device() { return &pDevice_; }
		ID3D11DeviceContext** Context() { return &pContext_; }

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

		ID3D11Device* pDevice_;          // デバイス
		ID3D11DeviceContext* pContext_;  // デバイスコンテキスト

		//IDXGIDevice1* pDXGI_;     // 複数ディスプレイ制御 // TODO なぜDeviceとDevice1があるのかを調べる
		//IDXGIAdapter* pAdapter_;  // 
		//IDXGIFactory* pFactory_;  // 
	};
}
