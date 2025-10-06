#pragma once
#include <DirectXMath.h>

namespace wtgb
{
	struct Vector3 : public DirectX::XMFLOAT3
	{
		// コンストラクタもそのまま継承
		using DirectX::XMFLOAT3::XMFLOAT3;
	};
}
