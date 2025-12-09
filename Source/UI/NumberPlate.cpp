#include "pch\pch.h"
#include "NumberPlate.h"

namespace
{
	// 数字のもととなる画像のファイル名
	const char NUMBER_IMAGE_FILE[]{ "Image/Numbers.png" };
}

NumberPlate::NumberPlate() : GameObject
{
	[](GameObjectBuilder& _builder)
	{
		_builder
			.AddComponent<GameObjectProperty>()
				.BeginSetter()
					.name("NumberPlate")
				.EndSetter()
		.Build();
	}
},
	hNumberImage_{},
	beginDrawPos_{},
	currDrawPos_{},
	sizePix_{},
	marginPix_{},
	number_{}
{
}

NumberPlate::~NumberPlate()
{
}

void NumberPlate::Init()
{
	hNumberImage_ = System().Get<ResourceSystem>().LoadTexture(NUMBER_IMAGE_FILE);
}

void NumberPlate::Update()
{
	currDrawPos_ = beginDrawPos_;
	
	for (std::string str = std::to_string(number_); char c : str)
	{
		if ('0' <= c && c <= '9')
		{
			NUMBER num{ c - '0' };
			DrawNumber(num);
		}
	}
}

void NumberPlate::Release()
{
}

void NumberPlate::DrawNumber(const NUMBER _number)
{
	const Canvas::Context& context{ System().Get<Canvas>().GetContext() };
	Texture* pTexture{ System().Get<ResourceSystem>().GetTexture(hNumberImage_) };

	wassert(pTexture && "テクスチャの取得に失敗");

	if (pTexture == nullptr)
	{
		return;
	}

	// 文字の幅 pixel
	int widthPix{ pTexture->GetImageSizePix().y };
	float widthPixF{ static_cast<float>(widthPix)};

	context.SetLayout(Canvas::LayoutConfig{}
		.position({ static_cast<float>(currDrawPos_.x), static_cast<float>(currDrawPos_.y) })
		.scale({ static_cast<float>(sizePix_.x), static_cast<float>(sizePix_.y) }));

	RectF rect{ widthPixF * _number, 0.0f, widthPixF, widthPixF };

	LOGFLN("({}, {}) ({}, {})", rect.x, rect.y, rect.width, rect.height);

	context.DrawImage(
		hNumberImage_,
		0.0f,
		rect);

	// 書いたら横移動
	currDrawPos_.x += sizePix_.x + marginPix_;

}
