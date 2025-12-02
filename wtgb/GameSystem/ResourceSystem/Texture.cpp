#include "pch\pch.h"
#include "Texture.h"
#include "WTGBAssert.h"
#include "GameSystem/Path.h"

wtgb::Texture::Texture(const Config& _config) :
	config_{ _config },
	imageSize_{ 0, 0 }
{
}

wtgb::Texture::~Texture()
{
}

void wtgb::Texture::Init()
{
}

void wtgb::Texture::Release()
{
	// 明示的に解放

	pSamplerState_.Reset();
	pShaderResourceView_.Reset();
}

void wtgb::Texture::CreateSamplerState(ID3D11Device* _pDevice)
{
	// テクスチャのサンプリング設定
	const D3D11_SAMPLER_DESC DESC
	{
		.Filter = config_.filer,  // MEMO: 線形補間もハードウェアでやってくれる
		.AddressU = config_.addressMode,  // 繰り返す
		.AddressV = config_.addressMode,
		.AddressW = config_.addressMode,
		.MipLODBias = {},
		.MaxAnisotropy = {},
		.ComparisonFunc = {},
		.BorderColor = {},
		.MinLOD = {},
		.MaxLOD = {},
	};

	HRESULT hResult{};
	hResult = _pDevice->CreateSamplerState(&DESC, pSamplerState_.GetAddressOf());
	if (FAILED(hResult))
	{
		wassert(false && "サンプラステートの作成に失敗");
		return;
	}
}

void wtgb::Texture::CreateShaderResourceView(ID3D11Device* _pDevice)
{
	using namespace DirectX;

	TexMetadata metaData{};  // 画像の付属データ
	ScratchImage image{};    // 画像本体

	HRESULT hResult{};

	std::wstring fileNameW{ config_.fileName.begin(), config_.fileName.end() };

	bool existFile{ Path::Current::Exists(fileNameW) };

	if (existFile == false)
	{
		wassert(false && "読み込むファイルが存在しない");
		return;
	}

	hResult = LoadFromWICFile(
		fileNameW.c_str(),
		WIC_FLAGS::WIC_FLAGS_NONE,
		&metaData,
		image);
	if (FAILED(hResult))
	{
		wassert(false && "テクスチャ画像読み込みに失敗");
		return;
	}

	imageSize_.x = static_cast<int>(metaData.width);
	imageSize_.y = static_cast<int>(metaData.height);

	const D3D11_SHADER_RESOURCE_VIEW_DESC DESC
	{
		.Format = config_.format,
		.ViewDimension = config_.dimension,
		.Texture2D
		{
			.MostDetailedMip = 0,
			.MipLevels = 1,  // LODのミップマップレベル
		},
	};

	//HRESULT hResult{};

	hResult = DirectX::CreateShaderResourceView(
		_pDevice,
		image.GetImages(),
		image.GetImageCount(),
		metaData,
		pShaderResourceView_.GetAddressOf());
	if (FAILED(hResult))
	{
		wassert(false && "シェーダリソースビューの作成に失敗");
		return;
	}
}
