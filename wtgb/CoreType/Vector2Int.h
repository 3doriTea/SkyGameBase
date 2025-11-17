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

#pragma region オペレーターオーバーロード - 四則演算
		inline Vector2Int& operator*=(const int& _scalar) { x *= _scalar; y *= _scalar; return *this; }
		inline Vector2Int& operator/=(const int& _scalar) { x /= _scalar; y /= _scalar; return *this; }
		inline Vector2Int& operator+=(const Vector2Int& _other) { x += _other.x; y += _other.y; return *this; }
		inline Vector2Int& operator-=(const Vector2Int& _other) { x -= _other.x; y -= _other.y; return *this; }
#pragma endregion

#pragma region よく使うベクトル
		/// <summary>
		/// 零ベクトル
		/// </summary>
		/// <returns>(0, 0)</returns>
		inline static Vector2Int Zero() { return { 0, 0 }; }
#pragma endregion
	};

#pragma region グローバルオペレーターオーバーロード - 四則演算
	inline Vector2Int operator*(const Vector2Int& _v, const int& _scalar) { return Vector2Int{ _v } *= _scalar; }
	inline Vector2Int operator*(const int& _scalar, const Vector2Int& _v) { return Vector2Int{ _v } *= _scalar; }
	inline Vector2Int operator/(const Vector2Int& _v, const int& _scalar) { return Vector2Int{ _v } /= _scalar; }
	inline Vector2Int operator/(const int& _scalar, const Vector2Int& _v) { return Vector2Int{ _v } /= _scalar; }
	inline Vector2Int operator+(const Vector2Int& _v1, const Vector2Int& _v2) { return Vector2Int{ _v1 } += _v2; }
	inline Vector2Int operator-(const Vector2Int& _v1, const Vector2Int& _v2) { return Vector2Int{ _v1 } -= _v2; }
#pragma endregion

#pragma region グローバルオペレーターオーバーロード - 等式
	inline bool operator==(const Vector2Int& _v1, const Vector2Int& _v2) { return _v1.x - _v2.x == 0 && _v1.y - _v2.y == 0; }
	inline bool operator!=(const Vector2Int& _v1, const Vector2Int& _v2) { return !(_v1 == _v2); }
#pragma endregion
}
