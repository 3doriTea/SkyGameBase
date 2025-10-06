#pragma once
#include <DirectXMath.h>

namespace wtgb
{
	struct Vector2Int : public DirectX::XMINT2
	{
		// コンストラクタもそのまま継承
		using DirectX::XMINT2::XMINT2;
	};
}
