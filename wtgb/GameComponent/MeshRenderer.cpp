#include "pch/pch.h"
#include "MeshRenderer.h"
#include "GameSystem/ResourceSystem.h"
#include "GameSystem/ShaderCompile.h"
#include "GameComponent/ModelMesh.h"

wtgb::MeshRenderer::MeshRenderer() :
	hShader_{ INVALID_HANDLE },
	hTexture_{ INVALID_HANDLE }
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
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },      // UV座標
				{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },  // 法線ベクトル
			},
			.fillMode = D3D11_FILL_SOLID,  // 塗りつぶし
			.cullMode = D3D11_CULL_BACK,   // 隠面消去
			.backIsClockwise = false,
		});
	hTexture_ = _system.Get<ResourceSystem>().LoadTexture(texture_);
}
