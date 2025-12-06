#pragma once
#include <variant>
#include "pch/pch.h"

namespace wtgb::UI
{
	enum struct RenderContentType
	{
		Image,  // ‰æ‘œ‚Ì•`‰æ
		Box,    // lŠpŒ`‚Ì•`‰æ
	};

	struct RenderContentImage
	{
		TextureHandle hTexture_;  // ƒeƒNƒXƒ`ƒƒƒnƒ“ƒhƒ‹
		float angle_;  // ‰ñ“]Šp“x
	};

	struct RenderContentBox
	{
		Color color;  // F
		float angle_;  // ‰ñ“]Šp“x
	};

	/// <summary>
	/// •`‰æ‚·‚é“à—e
	/// </summary>
	template<RenderContentType Type>
	class RenderContent
	{
	public:
		RenderContent(const TextureHandle _hTexture, float _angle)
			requires (Type == RenderContentType::Image) :
			image{ .hTexture_ = _hTexture, .angle_ = _angle }
		{
		}

		RenderContent(const Color _color, float _angle)
			requires (Type == RenderContentType::Box) :
			box{ .color = _color, .angle_ = _angle }
		{
		}

		void Render() requires (Type == RenderContentType::Image) {}
		void Render() requires (Type == RenderContentType::Box) {}

	private:
		union
		{
			RenderContentImage image;  // ‰æ‘œ
			RenderContentBox box;      // lŠpŒ`
		};
	};

	/// <summary>
	/// •`‰æ“à—e‚Ì‹¤’ÊŒ^
	/// </summary>
	using RenderContentVT = std::variant<
		RenderContent<RenderContentType::Image>,
		RenderContent<RenderContentType::Box>>;
}
