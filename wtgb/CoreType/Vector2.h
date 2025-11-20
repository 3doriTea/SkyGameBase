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

		Vector2(const DirectX::XMVECTOR& _xmV)
		{
			DirectX::XMStoreFloat2(this, _xmV);
		}

		/// <summary>
		/// XMVECTORに暗黙的変換する
		/// </summary>
		inline operator DirectX::XMVECTOR() const { return DirectX::XMLoadFloat2(this); }

	};
}
