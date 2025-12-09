#include "pch\pch.h"
#include "TestArrowUI.h"

using namespace wtgb;

TestArrowUI::TestArrowUI() : GameObject
{
	[this](GameObjectBuilder& _builder)
	{
		_builder
			.AddComponent<GameObjectProperty>()
				.BeginSetter()
					.name("TestArrowUI")
				.EndSetter()
			.AddComponent<wtgb::Transform>()
				.BeginSetter()
				.EndSetter()
		.Build();
	}
}
{
}

TestArrowUI::~TestArrowUI()
{
}

void TestArrowUI::Init()
{
	ResourceSystem& resourceSystem{ System().Get<ResourceSystem>() };

	hArrowTexture_ = resourceSystem.LoadTexture("Image/TestArrow.png");
}

void TestArrowUI::Update()
{
	ResourceSystem& resourceSystem{ System().Get<ResourceSystem>() };
	const Canvas::Context& context{ System().Get<Canvas>().GetContext() };
	Cursor& cursor{ System().Get<Cursor>() };

	Texture* pArrowTexture{ resourceSystem.GetTexture(hArrowTexture_) };

	/*context.SetLayout(
		Canvas::LayoutConfig{}
		.position({ static_cast<float>(cursor.GetPosition().x), static_cast<float>(cursor.GetPosition().y) })
		.positionPivot(UI::Pivot::TopLeft));*/

	//context.DrawBox(Color::BLUE);
	
	Vector2Int size{ pArrowTexture->GetImageSizePix() };

	context.SetLayout(
		Canvas::LayoutConfig{}
		.position({ static_cast<float>(cursor.GetPosition().x), static_cast<float>(cursor.GetPosition().y) })
		.positionPivot(UI::Pivot::TopLeft)
		.scale({ static_cast<float>(size.x), static_cast<float>(size.y) }));
	
	context.DrawImage(hArrowTexture_);
	
}

void TestArrowUI::Release()
{
}
