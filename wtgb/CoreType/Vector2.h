#pragma once
#include <DirectXMath.h>

namespace wtgb
{
	/// <summary>
	/// 2次元ベクトルを扱う構造体
	/// </summary>
	struct Vector2 : public DirectX::XMFLOAT2
	{
		// コンストラクタもそのまま継承
		using DirectX::XMFLOAT2::XMFLOAT2;
	};
}
