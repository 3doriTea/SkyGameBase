#include "pch\pch.h"
#include "TestArrowUI.h"
#include "UI/NumberPlate.h"


using namespace wtgb;

TestArrowUI::TestArrowUI(const EntityId _numberPlate) : GameObject
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
},
	numberPlate_{ _numberPlate }
{
}

TestArrowUI::~TestArrowUI()
{
}

void TestArrowUI::Init()
{
	NumberPlate* pNumberPlate{ dynamic_cast<NumberPlate*>(FindGameObject(numberPlate_)) };

	pNumberPlate->SetSize({ 300, 300 });
	pNumberPlate->SetPosition({});

	ResourceSystem& resourceSystem{ System().Get<ResourceSystem>() };

	hArrowTexture_ = resourceSystem.LoadTexture("Image/TestArrow.png");
}

void TestArrowUI::Update()
{
	ResourceSystem& resourceSystem{ System().Get<ResourceSystem>() };
	const Canvas::Context& context{ System().Get<Canvas>().GetContext() };
	Cursor& cursor{ System().Get<Cursor>() };
	const Input::InputGetter& input{ System().Get<Input>().Getter() };

	NumberPlate* pNumberPlate{ dynamic_cast<NumberPlate*>(FindGameObject(numberPlate_)) };

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
	
	//context.DrawImage(hArrowTexture_);

	if (input.IsKeyDown(KeyCode::T))
	{
		uint32_t num{ pNumberPlate->GetNumber() };
		num++;
		pNumberPlate->SetNumber(num);
	}
}

void TestArrowUI::Release()
{
}
