#pragma once
#include <wtgb.h>

class Button : public GameObject
{
public:
	Button();
	~Button();

	void SetOnImage(const TextureHandle _hOnImage);
	void SetOffImage(const TextureHandle _hOffImage);

	void Init() override;
	void Update() override;
	void Release() override;
	
	/// <summary>
	/// ボタンの左上の描画位置をピクセル単位で指定する
	/// </summary>
	/// <param name="_position"></param>
	void SetPosition(const Vector2Int _position) { position_ = _position; }
	/// <summary>
	/// ボタンのサイズをピクセル単位で指定する
	/// </summary>
	/// <param name="_size"></param>
	void SetSize(const Vector2Int _size) { size_ = _size; }

	/// <summary>
	/// 現在のフレームでボタンが押されたか
	/// </summary>
	/// <returns>押された true / false</returns>
	bool IsPushedFrame() const { return isPushedFrame_; }

	/// <summary>
	/// ボタンが押し込まれているか (まだ離されていない)
	/// </summary>
	/// <returns></returns>
	bool IsPressing() const { return isPressing_; }

	/// <summary>
	/// カーソルがボタン上にあるか
	/// </summary>
	/// <returns></returns>
	bool IsOnCursor() const { return isOnCursor_; }

private:
	bool isPushedFrame_;  // ボタンが押されたフレームか
	bool isOnCursor_;     // ボタンがカーソルに触れているか
	bool isPressing_;     // ボタンが押し込まれているか

	Vector2Int size_;
	Vector2Int position_;
	TextureHandle hOnImage_;
	TextureHandle hOffImage_;
};
