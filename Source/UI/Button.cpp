#include "pch\pch.h"
#include "Button.h"

Button::Button() :
	GameObject{ "Simple.json" },
	isPushedFrame_{ false },
	isOnCursor_{ false },
	size_{ Vector2Int::Zero() },
	position_{ Vector2Int::Zero() },
	hOnImage_{ INVALID_HANDLE },
	hOffImage_{ INVALID_HANDLE }
{
}

Button::~Button()
{
}

void Button::SetOnImage(const TextureHandle _hOnImage)
{
	hOnImage_ = _hOnImage;
}

void Button::SetOffImage(const TextureHandle _hOffImage)
{
	hOffImage_ = _hOffImage;
}

void Button::Init()
{
	
}

void Button::Update()
{
	Cursor& cursor{ System().Get<Cursor>() };
	const Input::InputGetter& input{ System().Get<Input>().Getter() };
	const Canvas::Context& context{ System().Get<Canvas>().GetContext() };

	Vector2Int cursorPos{ cursor.GetPosition() };
	Vector2Int begin{ position_ };
	Vector2Int end{ position_ + size_ };

	if (isPushedFrame_)
	{
		// 前が押されたフレームだったのなら戻す
		isPushedFrame_ = false;
	}

	isOnCursor_ =  // カーソルが範囲内かチェック
	{
		begin.x <= cursorPos.x && cursorPos.x <= end.x
		&& begin.y <= cursorPos.y && cursorPos.y <= end.y
	};
	if (isOnCursor_)
	{
		if (input.IsMouseDown(MouseCode::Left))
		{
			// ボタンの押し込み開始
			isPressing_ = true;
		}
	}
	else  // カーソルが範囲外なら押し込みありえない
	{
		isPressing_ = false;
	}

	if (isPressing_ && input.IsMouseUp(MouseCode::Left))
	{  // 押し込み状態でマウス左ボタン離されたなら
		isPushedFrame_ = true;  // このフレームでボタンが押された！
		isPressing_ = false;
	}

	TextureHandle hImage
	{
		isPressing_ ? hOnImage_ : hOffImage_
	};

	UI::LayoutConfig config{};
	config
		.position(position_)
		.scale(size_);

	context.SetRefLayout(&config);
	context.DrawImage(hImage);
}

void Button::Release()
{
}
