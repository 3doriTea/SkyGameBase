#include "pch\pch.h"
#include "../Canvas.h"
#include "GameSystem/ShaderCompile.h"
#include "GameSystem/ResourceSystem.h"

wtgb::UI::CanvasContext::CanvasContext(Canvas* _pCanvas) :
	Accessor{ _pCanvas },
	IResource{},
	system_{ nullptr },
	hBoxShader_{ INVALID_HANDLE },
	hImageShader_{ INVALID_HANDLE }
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
				.cullMode = D3D11_CULL_NONE,   // 隠面消去しない
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

void wtgb::UI::CanvasContext::SetRefLayout(LayoutConfig* _pConfig) const
{
	GetAccess()->pReferenceLayoutConfig_ = _pConfig;
}

void wtgb::UI::CanvasContext::DrawBox(const Color _color, const float _angle) const
{
	AddRenderOrder(RenderContentBox{ _color, _angle, hBoxShader_ });
}

void wtgb::UI::CanvasContext::DrawImage(const TextureHandle _hTexture, const float _angle, const RectF& _cut) const
{
	Texture* pTexture{ system_.Get<ResourceSystem>().GetTexture(_hTexture) };
	wassert(pTexture && "テクスチャの取得に失敗");
	if (pTexture == nullptr)
	{
		return;
	}

	const Vector2Int IMAGE_SIZE_PIX{ pTexture->GetImageSizePix() };

	RectF cut{ _cut };

	// カットサイズが無効なら元の画像サイズそのまま提供する
	if (cut.size.x <= 0.0f || cut.size.y <= 0.0f)
	{
		cut.point = Vector2::Zero();
		cut.size = { IMAGE_SIZE_PIX.x, IMAGE_SIZE_PIX.y };
	}

	AddRenderOrder(RenderContentImage{ _hTexture, _angle, cut, { IMAGE_SIZE_PIX.x, IMAGE_SIZE_PIX.y }, hImageShader_});
}

void wtgb::UI::CanvasContext::AddRenderOrder(const RenderContentVT& _content) const
{
	// キャンバスの参照を取っておく
	Canvas& canvas{ *GetAccess() };

	ConfigAndContent contentAndConfig{ {}, _content };
	auto& [config, content] = contentAndConfig;

	LayoutConfig* pRefConfig{ canvas.pReferenceLayoutConfig_ };
	if (pRefConfig != nullptr)
	{  // 参照があるならコピーして使用
		config = *pRefConfig;
	}

	// 描画オーダーで適切な場所に挿入する
	for (auto itr = canvas.renderOrder_.begin();
		itr != canvas.renderOrder_.end();
		itr++)
	{
		if (auto& [pickConfig, pickContent] = *itr;
			pickConfig.order_ > config.order_)  // 調べた要素がデカかったらその手前に挿入
		{
			canvas.renderOrder_.insert(itr, contentAndConfig);
			return;  // 挿入できたため回帰
		}
	}

	// もし見つからなければ最後に追加
	canvas.renderOrder_.push_back(contentAndConfig);
}
