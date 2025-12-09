#include "pch\pch.h"  
#include "../Canvas.h"  
#include "GameSystem/ShaderCompile.h"
#include "GameSystem/ResourceSystem.h"

wtgb::UI::CanvasContext::CanvasContext(Canvas* _pCanvas) :
	Accessor{ _pCanvas },
	IResource{},
	system_{ nullptr }
{
}

void wtgb::UI::CanvasContext::Init(ViewerCached _system)
{
	system_ = _system;

	ShaderCompile& shaderCompiler{ _system.Get<ShaderCompile>() };

	// 2Dシェーダに共通するコンパイル設定
	auto shader2DConfig
	{
		[](const std::string& _fileName) -> ShaderCompile::CompileConfig
		{
			return ShaderCompile::CompileConfig
			{
				.fileName = _fileName,
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
					{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },   // UV
				},
				.fillMode = D3D11_FILL_SOLID,  // 塗りつぶし
				.cullMode = D3D11_CULL_BACK,   // 隠面消去しない
				.backIsClockwise = false,
			};
		}
	};

	hBoxShader_ = shaderCompiler.Compile(shader2DConfig("Shader/Figure2D.hlsl"));
	hImageShader_ = shaderCompiler.Compile(shader2DConfig("Shader/Image2D.hlsl"));
}

void wtgb::UI::CanvasContext::Release(ViewerCached _system)
{
}

void wtgb::UI::CanvasContext::SetLayout(const LayoutConfig& _config)
{  
   currentConfig_ = _config;  
}  

void wtgb::UI::CanvasContext::DrawBox(const Color _color, const float _angle)  
{
	AddRenderOrder(RenderContentBox{ _color, _angle, hBoxShader_ });
}

void wtgb::UI::CanvasContext::DrawImage(const TextureHandle _hTexture, const float _angle, const RectF& _cut)
{
	Texture* pTexture{ system_.Get<ResourceSystem>().GetTexture(_hTexture) };
	wassert(pTexture && "テクスチャの取得に失敗");

	AddRenderOrder(RenderContentImage{ _hTexture, _angle, _cut, pTexture->GetImageSizePix(), hImageShader_ });
}

void wtgb::UI::CanvasContext::AddRenderOrder(const RenderContentVT& _content)  
{  
   GetAccess()->renderOrder_.push_back({ currentConfig_, _content });  
}
