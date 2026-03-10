#include "pch\pch.h"
#include "ResourceSystem.h"
#include "Direct3D.h"
#include "WTGBAssert.h"

wtgb::ResourceSystem::ResourceSystem() :
	system_{ nullptr }
{
}

wtgb::ResourceSystem::~ResourceSystem()
{
}

wtgb::Result wtgb::ResourceSystem::Init(const ViewerInit& _viewer)
{
	system_ = _viewer.GetCache();

	return Result::Code::Ok;
}

void wtgb::ResourceSystem::End()
{
	textures_.Release([](Texture& _texture)
		{
			_texture.CallRelease();
		});
}

wtgb::TextureHandle wtgb::ResourceSystem::LoadTexture(const fs::path& _fileName)
{
	return LoadTexture(Texture::Config
		{
			.fileName = _fileName.string(),
			.filer = D3D11_FILTER_MIN_MAG_MIP_LINEAR,    // 線形補間する
			.addressMode = D3D11_TEXTURE_ADDRESS_CLAMP,  // 端っこは繰り返す
			.format = DXGI_FORMAT_R8G8B8A8_UNORM,        // DXGIフォーマット
			.dimension = D3D11_SRV_DIMENSION_TEXTURE2D,  // 2次元のテクスチャ想定
		});
}

wtgb::TextureHandle wtgb::ResourceSystem::LoadTexture(const std::string& _fileName)
{
	return LoadTexture(Texture::Config
		{
			.fileName = _fileName,
			.filer = D3D11_FILTER_MIN_MAG_MIP_LINEAR,    // 線形補間する
			.addressMode = D3D11_TEXTURE_ADDRESS_CLAMP,  // 端っこは繰り返す
			.format = DXGI_FORMAT_R8G8B8A8_UNORM,        // DXGIフォーマット
			.dimension = D3D11_SRV_DIMENSION_TEXTURE2D,  // 2次元のテクスチャ想定
		});
}

wtgb::TextureHandle wtgb::ResourceSystem::LoadTexture(const char* _fileName)
{
	return LoadTexture(fs::path{ _fileName });
}

wtgb::TextureHandle wtgb::ResourceSystem::LoadTexture(const Texture::Config& _config)
{
	ID3D11Device* pDevice{ system_.Get<Direct3D>().Resource().Device() };

	TextureHandle hTexture = textures_.Emplace(_config);

	// 初期化していく
	textures_.At(hTexture).CallInit();
	textures_.At(hTexture).CreateSamplerState(pDevice);
	textures_.At(hTexture).CreateShaderResourceView(pDevice);

	return hTexture;
}

wtgb::Texture* wtgb::ResourceSystem::GetTexture(const std::string& _fileName)
{
	// TODO: ファイル名をmapで保存しておく
	wassert(false && "早く実装してください");

	return nullptr;
}

wtgb::Texture* wtgb::ResourceSystem::GetTexture(const TextureHandle _hTexture)
{
	try
	{
		return &textures_.At(_hTexture);
	}
	catch (const std::string& e)
	{
		(void)e;  // 明示的に使用
		wassert(false && "無効なテクスチャハンドルが指定された");
		return nullptr;
	}
}
