#pragma once
#include "pch/pch.h"
#include "Utility/IResource.h"
#include "Utility/Accessor.h"

namespace wtgb
{
	/// <summary>
	/// 読み込んだシェーダ
	/// </summary>
	class Shader : public IResource<>
	{
	public:
		/// <summary>
		/// シェーダへのアクセッサ
		/// </summary>
		class ShaderAccessor : public Accessor<Shader>
		{
		private:
			using Accessor<Shader>::Accessor;
		public:
			~ShaderAccessor() {}

		public:
			ComPtr<ID3D11VertexShader>& VertexShader() const { return GetAccess()->VertexShader(); }
			ComPtr<ID3D11PixelShader>& PixelShader() const { return GetAccess()->PixelShader(); }
			ComPtr<ID3D11InputLayout>& InputLayout() const { return GetAccess()->VertexLayout(); }
			ComPtr<ID3D11RasterizerState>& RasterizerState() const { return GetAccess()->RasterizerState(); }
		};
	public:
		Shader(const std::string& _fileName);
		~Shader();

		ComPtr<ID3D11VertexShader>& VertexShader() { return pVertexShader_; }
		ComPtr<ID3D11PixelShader>& PixelShader() { return pPixelShader_; }
		ComPtr<ID3D11InputLayout>& VertexLayout() { return pVertexLayout_; }
		ComPtr<ID3D11RasterizerState>& RasterizerState() { return pRasterizerState_; }
		ShaderAccessor& GetAccessor() { return accessor_; }

		std::string_view GetFileName() { return fileName_; }

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
		ShaderAccessor accessor_;  // アクセッサ
		std::string fileName_;  // ファイル名
	};
}
