#pragma once
#include "pch/pch.h"
#include "Utility/IResource.h"

namespace wtgb
{
	class Shader : public IResource
	{
	public:
		Shader();
		~Shader();

		ComPtr<ID3D11VertexShader>& VertexShader() { return pVertexShader_; }
		ComPtr<ID3D11PixelShader>& PixelShader() { return pPixelShader_; }
		ComPtr<ID3D11InputLayout>& VertexLayout() { return pVertexLayout_; }
		ComPtr<ID3D11RasterizerState>& RasterizerState() { return pRasterizerState_; }

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
		ComPtr<ID3D11VertexShader> pVertexShader_;        // 頂点シェーダ
		ComPtr<ID3D11PixelShader> pPixelShader_;          // ピクセルシェーダ
		ComPtr<ID3D11InputLayout> pVertexLayout_;         // 頂点インプットレイアウト
		ComPtr<ID3D11RasterizerState> pRasterizerState_;  // ラスタライザステート
	};
}
