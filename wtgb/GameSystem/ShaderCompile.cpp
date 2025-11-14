#include "pch\pch.h"
#include "ShaderCompile.h"

#include "WTGBAssert.h"
#include "Direct3D.h"

#include "Direct3D.h"

wtgb::ShaderCompile::ShaderCompile() :
	system_{ nullptr }
{
}

wtgb::ShaderCompile::~ShaderCompile()
{
}

wtgb::Result wtgb::ShaderCompile::Init(const ViewerInit& _viewer)
{
	system_ = _viewer.GetCache();
	return Result::Code::Ok;
}

void wtgb::ShaderCompile::Update(const ViewerUpdate& _system)
{
}

void wtgb::ShaderCompile::End()
{
}

const wtgb::ShaderHandle wtgb::ShaderCompile::Compile(const CompileConfig& _config)
{
	std::string_view fileName{ _config.fileName };
	
	// 重複を探す
	ShaderHandle foundHandle
	{
		shaders_.GetContainsDuplicate([&fileName](Shader& _shader) -> bool
		{
			return _shader.GetFileName() == fileName;
		})
	};

	if (foundHandle != INVALID_HANDLE)
	{
		// 重複があるならそのハンドルを返す
		return foundHandle;
	}

	ShaderHandle hShader{ shaders_.Emplace(_config.fileName) };

	ID3D11Device* pDevice{ system_.Get<Direct3D>().Resource().Device() };

	HRESULT hResult{};
	ComPtr<ID3DBlob> pError{ nullptr };
	ComPtr<ID3DBlob> pCompileVS{ nullptr };
	ComPtr<ID3DBlob> pCompilePS{ nullptr };

#pragma region 頂点シェーダのコンパイル
	std::wstring fileNameW{ _config.fileName.begin(), _config.fileName.end() };

	// 頂点シェーダをファイルからコンパイル
	hResult = D3DCompileFromFile(
		fileNameW.c_str(),
		_config.pDefines,
		_config.pInclude,
		_config.vertexShader.entryPointName.c_str(),
		_config.vertexShader.compileVersion.c_str(),
		_config.flag1,
		_config.flag2,
		pCompileVS.GetAddressOf(),
		pError.GetAddressOf());
	wassert(SUCCEEDED(hResult) && "頂点シェーダのコンパイルに失敗");
	if (FAILED(hResult))
	{
		LOGFLN("頂点シェーダコンパイルエラー：{}", reinterpret_cast<char*>(pError.Get()));
		// 失敗したなら無効ハンドルを返す
		return INVALID_HANDLE;
	}

	hResult = pDevice->CreateVertexShader(
		pCompileVS->GetBufferPointer(),
		pCompileVS->GetBufferSize(),
		nullptr,
		shaders_.At(hShader).VertexShader().GetAddressOf());
	wassert(SUCCEEDED(hResult) && "頂点シェーダの作成に失敗");
	if (FAILED(hResult))
	{
		// 失敗したなら無効ハンドルを返す
		return INVALID_HANDLE;
	}
#pragma endregion

#pragma region 頂点インプットレイアウト
	hResult = pDevice->CreateInputLayout(
		_config.vertexInputLayout.data(),
		static_cast<UINT>(_config.vertexInputLayout.size()),
		pCompileVS->GetBufferPointer(),
		pCompileVS->GetBufferSize(),
		shaders_.At(hShader).VertexLayout().GetAddressOf());
	wassert(SUCCEEDED(hResult) && "頂点インプットレイアウトの作成失敗");
	if (FAILED(hResult))
	{
		// 失敗したなら無効ハンドルを返す
		return INVALID_HANDLE;
	}
#pragma endregion

#pragma region ピクセルシェーダ
	// ピクセルシェーダをファイルからコンパイル
	hResult = D3DCompileFromFile(
		fileNameW.c_str(),
		_config.pDefines,
		_config.pInclude,
		_config.pixelShader.entryPointName.c_str(),
		_config.pixelShader.compileVersion.c_str(),
		_config.flag1,
		_config.flag2,
		pCompilePS.GetAddressOf(),
		pError.GetAddressOf());
	wassert(SUCCEEDED(hResult) && "ピクセルシェーダのコンパイルに失敗");
	if (FAILED(hResult))
	{
		LOGFLN("ピクセルシェーダコンパイルエラー：{}", reinterpret_cast<char*>(pError.Get()));
		// 失敗したなら無効ハンドルを返す
		return INVALID_HANDLE;
	}

	hResult = pDevice->CreatePixelShader(
		pCompilePS->GetBufferPointer(),
		pCompilePS->GetBufferSize(),
		nullptr,
		shaders_.At(hShader).PixelShader().GetAddressOf());
	wassert(SUCCEEDED(hResult) && "ピクセルシェーダの作成に失敗");
	if (FAILED(hResult))
	{
		// 失敗したなら無効ハンドルを返す
		return INVALID_HANDLE;
	}
#pragma endregion

#pragma region ラスタライザ
	const D3D11_RASTERIZER_DESC RASTERIZER_DESC
	{
		.FillMode = _config.fillMode,
		.CullMode = _config.cullMode,
		.FrontCounterClockwise = _config.backIsClockwise,
		.DepthBias = {},
		.DepthBiasClamp = {},
		.SlopeScaledDepthBias = {},
		.DepthClipEnable = {},
		.ScissorEnable = {},
		.MultisampleEnable = {},
		.AntialiasedLineEnable = {},
	};
	// ラスタライザステートを作成する
	hResult = pDevice->CreateRasterizerState(
		&RASTERIZER_DESC,
		shaders_.At(hShader).RasterizerState().GetAddressOf());
	wassert(SUCCEEDED(hResult) && "ラスタライザステートの作成に失敗");
	if (FAILED(hResult))
	{
		// 失敗したなら無効ハンドルを返す
		return INVALID_HANDLE;
	}
#pragma endregion

	// 明示的に解放

	pError.Reset();
	pCompileVS.Reset();
	pCompilePS.Reset();

	return hShader;
}

wtgb::Shader::ShaderAccessor& wtgb::ShaderCompile::GetShader(const ShaderHandle _hShader)
{
	return shaders_.At(_hShader).GetAccessor();
}

ID3D11VertexShader* wtgb::ShaderCompile::GetVertexShader(const ShaderHandle _hShader)
{
	return shaders_.At(_hShader).VertexShader().Get();
}

ID3D11PixelShader* wtgb::ShaderCompile::GetPixelShader(const ShaderHandle _hShader)
{
	return shaders_.At(_hShader).PixelShader().Get();
}

ID3D11InputLayout* wtgb::ShaderCompile::GetInputLayout(const ShaderHandle _hShader)
{
	return shaders_.At(_hShader).VertexLayout().Get();
}

ID3D11RasterizerState* wtgb::ShaderCompile::GetRasterizerState(const ShaderHandle _hShader)
{
	return shaders_.At(_hShader).RasterizerState().Get();
}
