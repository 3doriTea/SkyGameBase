#pragma once
#include <wtgb.h>

/// <summary>
/// 数字を表示するUI
/// </summary>
class NumberPlate : public GameObject
{
	/// <summary>
	/// 数字
	/// </summary>
	enum NUMBER : int8_t
	{
		_0,
		_1,
		_2,
		_3,
		_4,
		_5,
		_6,
		_7,
		_8,
		_9,
	};
public:
	NumberPlate(const std::string_view _numberImageFilePath);
	~NumberPlate();

	void Init() override;
	void Update() override;
	void Release() override;

	/// <summary>
	/// 表示する数字の大きさ
	/// </summary>
	/// <param name="_size">大きさ(ピクセル単位)</param>
	void SetSize(const Vector2Int _size) { sizePix_ = _size; }

	/// <summary>
	/// 表示する数値を設定する
	/// </summary>
	/// <param name="_number">表示する符号なし32bit整数</param>
	void SetNumber(const uint32_t _number) { number_ = _number; }
	/// <summary>
	/// 現在表示する数値を取得する
	/// </summary>
	/// <returns>符号なし32bit整数</returns>
	uint32_t GetNumber() const { return number_; }
	/// <summary>
	/// 表示する座標 (左上基準) を設定する
	/// </summary>
	/// <param name="_drawPosition">描画座標</param>
	inline void SetPosition(const Vector2Int _drawPosition) { beginDrawPos_ = _drawPosition; }

	/// <summary>
	/// <para>設計時のキャンバスサイズを設定する</para>
	/// <para>(0.0, 0.0) で無効化</para>
	/// </summary>
	/// <param name="_size">設計時のキャンバスサイズ</param>
	inline void SetBaseCanvasSize(const Vector2Int _size) { baseCanvasSize_ = _size; }

private:
	/// <summary>
	/// 数字の描画処理
	/// </summary>
	/// <param name="_number">描画する数字の種類</param>
	void DrawNumber(const NUMBER _number);

private:
	uint32_t number_;                  // 表示する数値
	TextureHandle hNumberImage_;       // 数字の横長画像ハンドル
	Vector2Int baseCanvasSize_;        // 設計時のキャンバスサイズ
	Vector2Int beginDrawPos_;          // 描画座標
	Vector2Int currDrawPos_;           // 描画途中の座標
	Vector2Int sizePix_;               // 文字の描画サイズ
	int marginPix_;                    // 文字同士の余白
	std::string numberImageFilePath_;  // 数字の画像ファイルパス
};
