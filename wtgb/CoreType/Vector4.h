#pragma once
#include <DirectXMath.h>

namespace wtgb
{
	/// <summary>
	/// 4次元ベクトルを扱う構造体
	/// </summary>
	struct Vector4 : public DirectX::XMFLOAT4
	{
		// コンストラクタもそのまま継承
		using DirectX::XMFLOAT4::XMFLOAT4;

		Vector4(const DirectX::XMVECTOR& _xmV)
		{
			DirectX::XMStoreFloat4(this, _xmV);
		}

		/// <summary>
		/// XMVECTORに暗黙的変換する
		/// </summary>
		inline operator DirectX::XMVECTOR() const { return DirectX::XMLoadFloat4(this); }

		/// <summary>
		/// 零ベクトルを取得する
		/// </summary>
		/// <returns>(0, 0, 0, 0)</returns>
		inline static Vector4 Zero() { return { 0, 0, 0, 0 }; }
		/// <summary>
		/// Zだけ+1のベクトルを取得する
		/// </summary>
		/// <returns>(0, 0, 1, 0)</returns>
		inline static Vector4 Forward() { return { 0, 0, 1.0f, 0 }; }
		/// <summary>
		/// 全成分が1のベクトルを取得する
		/// </summary>
		/// <returns>(1, 1, 1, 1)</returns>
		inline static Vector4 One() { return { 1.0f, 1.0f, 1.0f, 1.0f }; }
	};
}
