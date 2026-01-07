#include "pch/pch.h"
#include "MeshRenderer.h"
#include "GameSystem/ResourceSystem.h"
#include "GameSystem/ShaderCompile.h"
#include "GameComponent/ModelMesh.h"
#include "GameSystem/CPMeshRenderer.h"

wtgb::MeshRenderer::MeshRenderer() :
	hShader_{ INVALID_HANDLE },
	hTexture_{ INVALID_HANDLE },
	texture_{},
	textureConfig_{}
{
}

void wtgb::MeshRenderer::Init(ViewerCached _system)
{
	hShader_ = _system.Get<ShaderCompile>().Compile(
		{
			.fileName = shader_,
			.vertexShader
			{
				.entryPointName = "VS",
				.compileVersion = "vs_5_0",
			},
			.pixelShader
			{
				.entryPointName = "PS",
				.compileVersion = "ps_5_0",
			},
			.vertexInputLayout
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },   // 位置
				{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },     // 法線ベクトル
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },      // UV座標
			},
			.fillMode = D3D11_FILL_SOLID,  // 塗りつぶし
			.cullMode = D3D11_CULL_BACK,   // 隠面消去
			//.cullMode = D3D11_CULL_NONE,   // 隠面消去
			.backIsClockwise = false,
		});

	// テクスチャのファイル名が"指定されている"なら設定して読み込み
	if (texture_.empty() == false)
	{
		hTexture_ = _system.Get<ResourceSystem>().LoadTexture(texture_);
	}
	// テクスチャ読み込み設定がされているなら、設定から読み込む
	else if (textureConfig_.fileName.empty() == false)
	{
		hTexture_ = _system.Get<ResourceSystem>().LoadTexture(textureConfig_);
	}
}
