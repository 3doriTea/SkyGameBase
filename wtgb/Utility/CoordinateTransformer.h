#pragma once

namespace wtgb
{
	/// <summary>
	/// デザインキャンバスとスクリーンキャンバスの差分を埋める
	/// </summary>
	class CoordinateTransformer
	{
	public:
		CoordinateTransformer(
			const Vector2Int _screenCanvasSize = Vector2Int::Zero(),
			const Vector2Int _designCanvasSize = Vector2Int::Zero());
		~CoordinateTransformer();

		/// <summary>
		/// スクリーンキャンバスサイズをセットする
		/// </summary>
		/// <param name="_size">サイズ</param>
		void SetScreenCanvasSize(const Vector2Int _size) { screenCanvasSize_ = _size; }
		/// <summary>
		/// デザインキャンバスサイズをセットする
		/// </summary>
		/// <param name="_size">サイズ</param>
		void SetDesignCanvasSize(const Vector2Int _size) { designCanvasSize_ = _size; }

		/// <summary>
		/// デザイン座標からスクリーン座標に変換する
		/// </summary>
		/// <param name="_position">デザイン座標</param>
		/// <returns>スクリーン座標</returns>
		Vector2Int ToScreenCoords(Vector2Int _position) const;
		/// <summary>
		/// デザイン座標からスクリーン座標に変換する
		/// </summary>
		/// <param name="_position">デザイン座標</param>
		/// <returns>スクリーン座標</returns>
		Vector2Int ToScreenCoords(Vector2 _position) const;

	private:
		Vector2Int screenCanvasSize_;  // スクリーンのサイズ
		Vector2Int designCanvasSize_;  // 設計時のサイズ
	};
}
