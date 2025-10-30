#include "pch\pch.h"
#include "ShaderCompile.h"

#include "WTGBAssert.h"
#include "Direct3D.h"

wtgb::ShaderCompile::ShaderCompile()
{
}

wtgb::ShaderCompile::~ShaderCompile()
{
}

wtgb::Result wtgb::ShaderCompile::Init(const ViewerInit& _viewer)
{
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
	ShaderHandle hShader{ shaders_.Emplace() };

	ID3D11Device* pDevice{ system_.Get<Direct3D>().Resource().Device() };

	HRESULT hResult{};
	ComPtr<ID3DBlob> pError{ nullptr };

#pragma region 頂点シェーダのコンパイル
	ComPtr<ID3DBlob> pCompileVS{ nullptr };

	std::wstring fileNameW{ _config.fileName.begin(), _config.fileName.end() };

	hResult = D3DCompileFromFile(
		fileNameW.c_str(),
		_config.pDefines,
		_config.pInclude,
		_config.target.entryPointName.c_str(),
		_config.target.compileVersion.c_str(),
		_config.flag1,
		_config.flag2,
		pCompileVS.GetAddressOf(),
		pError.GetAddressOf());
	wassert(SUCCEEDED(hResult) && "頂点シェーダのコンパイルに失敗");
	if (FAILED(hResult))
	{
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
	// TODO: 次頂点インプットレイアウト、そしてピクセルシェーダ、最後にラスタライザ
#pragma endregion

#pragma region 頂点インプットレイアウト
#pragma endregion

#pragma region ピクセルシェーダ
#pragma endregion

	pError.Reset();
}
