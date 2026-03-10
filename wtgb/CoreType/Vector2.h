#pragma once
#include <DirectXMath.h>
#include "Vector2T.h"
#include "Vector2Int.h"

namespace wtgb
{
	struct Vector2Int;

	/// <summary>
	/// 2次元ベクトルを扱う構造体
	/// </summary>
	struct Vector2 : public DirectX::XMFLOAT2
	{
		// コンストラクタもそのまま継承
		using DirectX::XMFLOAT2::XMFLOAT2;

		enum
		{
			AT_X,
			AT_Y,
			AT_Z,
		};

		Vector2(const DirectX::XMVECTOR& _xmV)
		{
			DirectX::XMStoreFloat2(this, _xmV);
		}

		Vector2(const mtgb::Vector2T<float> _v2) :
			DirectX::XMFLOAT2{ _v2.x, _v2.y }
		{
		}

		Vector2(const Vector2Int _v2) :
			DirectX::XMFLOAT2{ static_cast<float>(_v2.x), static_cast<float>(_v2.y) }
		{
		}

		/// <summary>
		/// XMVECTORに暗黙的変換する
		/// </summary>
		inline operator DirectX::XMVECTOR() const { return DirectX::XMLoadFloat2(this); }
		
		/// <summary>
		/// mtgb::Vector2T＜float＞ に暗黙的変換する
		/// </summary>
		inline operator mtgb::Vector2T<float>() const { return { x, y }; }

		/// <summary>
		/// 零ベクトルを取得する
		/// </summary>
		/// <returns>(0, 0)</returns>
		inline static Vector2 Zero() { return { 0.0f, 0.0f }; }

		/// <summary>
		/// Yだけ+1のベクトルを取得する
		/// </summary>
		/// <returns>(0, 1)</returns>
		inline static Vector2 Up() { return { 0.0f, 1.0f }; }

		/// <summary>
		/// XYともに+1のベクトルを取得する
		/// </summary>
		/// <returns>(1, 1)</returns>
		inline static Vector2 One() { return { 1.0f, 1.0f }; }
	};
}
