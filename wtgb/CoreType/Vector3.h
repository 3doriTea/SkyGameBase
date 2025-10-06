#pragma once
#include <DirectXMath.h>

namespace wtgb
{
	/// <summary>
	/// 3次元ベクトルを扱う構造体
	/// </summary>
	struct Vector3 : public DirectX::XMFLOAT3
	{
		// コンストラクタもそのまま継承
		using DirectX::XMFLOAT3::XMFLOAT3;
	};
}
