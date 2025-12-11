#include "pch\pch.h"
#include "ControlUI.h"

ControlUI::ControlUI() : GameObject
{
	[this](GameObjectBuilder& _builder)
	{
		_builder
			.AddComponent<GameObjectProperty>()
				.BeginSetter()
					.name("ControlUI")
				.EndSetter()
			.AddComponent<wtgb::Transform>()
				.BeginSetter()
				.EndSetter()
		.Build();
	}
},
	hCenterCircleImage_{ INVALID_HANDLE }
{
}

ControlUI::~ControlUI()
{
}

void ControlUI::Init()
{
	hCenterCircleImage_ = System().Get<ResourceSystem>().LoadTexture("Image/MouseCircle.png");
}

void ControlUI::Update()
{
	ResourceSystem& resourceSystem{ System().Get<ResourceSystem>() };
	const Canvas::Context& context{ System().Get<Canvas>().GetContext() };
	Cursor& cursor{ System().Get<Cursor>() };
	const Input::InputGetter& input{ System().Get<Input>().Getter() };
	const Vector2Int SCREEN_SIZE{ System().Get<GameWindow>().GetMainWindowSize() };
	const Vector2Int SCREEN_CENTER{ SCREEN_SIZE / 2 };

	Texture* pCenterCircleImage{ resourceSystem.GetTexture(hCenterCircleImage_) };
	wassert(pCenterCircleImage && "‰æ‘œ‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s");

	Vector2Int imageSize{ pCenterCircleImage->GetImageSizePix() };

	Vector2Int begin{ SCREEN_CENTER - (imageSize / 2) };

	context.SetLayout(UI::LayoutConfig{}
		.position({ static_cast<float>(begin.x), static_cast<float>(begin.y) })
		.scale({ static_cast<float>(imageSize.x), static_cast<float>(imageSize.y) }));

	context.DrawImage(hCenterCircleImage_);
}

void ControlUI::Release()
{
}
