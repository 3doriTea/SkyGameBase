#pragma once
#include "pch/pch.h"
#include "Utility/IResource.h"
#include "TextureConfig.h"

namespace wtgb
{
	/// <summary>
	/// 画像のテクスチャ
	/// </summary>
	class Texture : public IResource<>
	{
	public:
		using Config = TextureConfig;

	public:
		Texture(const Config& _config);
		~Texture();

	private:
		/// <summary>
		/// 初期化処理
		/// </summary>
		void Init() override;
		/// <summary>
		/// 解放処理
		/// </summary>
		void Release() override;

	public:
		inline ComPtr<ID3D11SamplerState>& GetSamplerState() { return pSamplerState_; }
		inline ComPtr<ID3D11ShaderResourceView>& GetShaderResourceView() { return pShaderResourceView_; }

	public:
		/// <summary>
		/// サンプラステートを作成する
		/// </summary>
		/// <param name="_pDevice">デバイス</param>
		void CreateSamplerState(ID3D11Device* _pDevice);
		/// <summary>
		/// シェーダリソースビューを作成する
		/// </summary>
		/// <param name="_pDevice">デバイス</param>
		void CreateShaderResourceView(ID3D11Device* _pDevice);

		/// <summary>
		/// 画像のサイズピクセルを取得する
		/// </summary>
		/// <returns>画像のサイズ</returns>
		inline Vector2Int GetImageSizePix() const { return imageSize_; }

	private:
		Config config_;  // 設定

		ComPtr<ID3D11SamplerState> pSamplerState_;              // サンプラーステート
		ComPtr<ID3D11ShaderResourceView> pShaderResourceView_;  // シェーダリソースビュー
		Vector2Int imageSize_;                                  // 画像ソースのサイズ
	};
}
