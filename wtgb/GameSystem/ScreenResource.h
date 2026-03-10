#pragma once
#include "pch/pch.h"

namespace wtgb
{
	class ScreenResource
	{
	public:
		ScreenResource();
		~ScreenResource();

	private:
		IDXGISwapChain* pSwapChain_;                 // ダブルバッファリングでバッファを切り替えるやつ
		ID3D11RenderTargetView* pRenderTargetView_;  // 描画先のビュー
		ID3D11Texture2D* pDepthStencil_;             // 深度バッファ
		ID3D11DepthStencilView* pDepthStencilView_;  // 深度バッファのビュー
	};
}
