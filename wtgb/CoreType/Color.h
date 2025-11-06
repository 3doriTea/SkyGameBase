#pragma once
#include <DirectXMath.h>

namespace wtgb
{
	/// <summary>
	/// 色を扱う
	/// </summary>
	struct Color : public DirectX::XMFLOAT4
	{
		// コンストラクタもそのまま継承
		using DirectX::XMFLOAT4::XMFLOAT4;

		Color(const uint32_t _hexCode) :
			XMFLOAT4
			{
				static_cast<float>(_hexCode & 0xff0000) / 255.0f,
				static_cast<float>(_hexCode & 0x00ff00) / 255.0f,
				static_cast<float>(_hexCode & 0x0000ff) / 255.0f,
				1.0f,
			}
		{
		}
	};
}
