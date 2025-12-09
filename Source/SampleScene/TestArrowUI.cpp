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
	const Canvas::Context& context{ System().Get<Canvas>().GetContext() };
	Cursor& cursor{ System().Get<Cursor>() };

	context.SetLayout(
		Canvas::LayoutConfig{}
		.position({ static_cast<float>(cursor.GetPosition().x), static_cast<float>(cursor.GetPosition().y) })
		.positionPivot(UI::Pivot::TopLeft));

	context.DrawImage(hArrowTexture_);
	

	context.SetLayout(
		Canvas::LayoutConfig{}
		.position({ static_cast<float>(cursor.GetPosition().x), static_cast<float>(cursor.GetPosition().y) })
		.positionPivot(UI::Pivot::TopLeft)
		.scale({ 30, 30 }));
	
	//context.DrawBox(Color::BLUE);
}

void TestArrowUI::Release()
{
}
