#pragma once
#include <DirectXMath.h>


namespace wtgb
{
	using ColorCode = uint32_t;

	/// <summary>
	/// 色を扱う
	/// </summary>
	struct Color : public DirectX::XMFLOAT4
	{

		// コンストラクタもそのまま継承
		using DirectX::XMFLOAT4::XMFLOAT4;

		Color(const ColorCode _hexCode, const uint8_t _alpha = UINT8_MAX) :
			XMFLOAT4
			{
				static_cast<float>((_hexCode & 0xff0000) >> (8 * 2)) / 255.0f,
				static_cast<float>((_hexCode & 0x00ff00) >> (8 * 1)) / 255.0f,
				static_cast<float>((_hexCode & 0x0000ff) >> (8 * 0)) / 255.0f,
				static_cast<float>(_alpha) / 255.0f,
			}
		{
		}

		static const ColorCode RED;
		static const ColorCode GREEN;
		static const ColorCode BLUE;
		static const ColorCode NONE;
		static const ColorCode FULL;
	};
}

inline const wtgb::ColorCode wtgb::Color::RED  { 0xff0000 };
inline const wtgb::ColorCode wtgb::Color::GREEN{ 0x00ff00 };
inline const wtgb::ColorCode wtgb::Color::BLUE { 0x0000ff };
inline const wtgb::ColorCode wtgb::Color::NONE { 0xffffffff };
inline const wtgb::ColorCode wtgb::Color::FULL { 0xffffffff };
