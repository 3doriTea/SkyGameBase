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

		operator DirectX::XMVECTOR() const { return DirectX::XMLoadFloat3(this); }

		static Vector3 Zero() { return { 0, 0, 0 }; }
		static Vector3 Forward() { return { 0, 0, 1.0f }; }
	};
}
