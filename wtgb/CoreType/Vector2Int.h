#pragma once
#include <DirectXMath.h>

namespace wtgb
{
	/// <summary>
	/// 2次元ベクトルを扱う構造体
	/// </summary>
	struct Vector2Int : public DirectX::XMINT2
	{
		// コンストラクタもそのまま継承
		using DirectX::XMINT2::XMINT2;
	};
}
