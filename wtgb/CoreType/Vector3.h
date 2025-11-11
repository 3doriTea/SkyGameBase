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

		Vector3(const DirectX::XMVECTOR& _xmV)
		{
			DirectX::XMStoreFloat3(this, _xmV);
		}

		/// <summary>
		/// XMVECTORに暗黙的変換する
		/// </summary>
		inline operator DirectX::XMVECTOR() const { return DirectX::XMLoadFloat3(this); }

		/// <summary>
		/// 零ベクトルを取得する
		/// </summary>
		/// <returns>(0, 0, 0)</returns>
		static Vector3 Zero() { return { 0, 0, 0 }; }
		/// <summary>
		/// Zだけ+1のベクトルを取得する
		/// </summary>
		/// <returns>(0, 0, 1)</returns>
		static Vector3 Forward() { return { 0, 0, 1.0f }; }

		/// <summary>
		/// 行列との掛け算
		/// </summary>
		/// <param name="_matrix">行列</param>
		/// <returns>3次元ベクトル</returns>
		inline Vector3& operator*=(const DirectX::XMMATRIX _matrix)
		{
			using DirectX::XMVECTOR;
			using DirectX::XMVector3TransformCoord;
			using DirectX::XMStoreFloat3;

			XMVECTOR v{ (XMVECTOR)(*this) };
			v = XMVector3TransformCoord(v, _matrix);
			XMStoreFloat3(this, v);

			return *this;
		}
	};
}
