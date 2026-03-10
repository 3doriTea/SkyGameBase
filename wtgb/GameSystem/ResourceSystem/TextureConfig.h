#pragma once

namespace wtgb
{
	/// <summary>
	/// テクスチャの設定
	/// </summary>
	struct TextureConfig
	{
		std::string fileName;                    // テクスチャ画像のファイル名
		D3D11_FILTER filer;                      // テクスチャの内部で線形補間等の設定
		D3D11_TEXTURE_ADDRESS_MODE addressMode;  // UV座標範囲外の描画モード

		DXGI_FORMAT format;                      // フォーマット
		D3D11_SRV_DIMENSION dimension;           // 何次元のテクスチャか設定
	};
}
