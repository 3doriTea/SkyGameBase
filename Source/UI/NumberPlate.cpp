#include "pch\pch.h"
#include "NumberPlate.h"


NumberPlate::NumberPlate(const std::string_view _numberImageFilePath) : GameObject
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
	baseCanvasSize_{ 1920, 1080 },
	sizePix_{},
	marginPix_{},
	number_{},
	numberImageFilePath_{ _numberImageFilePath }
{
}

NumberPlate::~NumberPlate()
{
}

void NumberPlate::Init()
{
	hNumberImage_ = System().Get<ResourceSystem>().LoadTexture(
		numberImageFilePath_);
}

void NumberPlate::Update()
{
	currDrawPos_ = beginDrawPos_;
	
	LOGFLN("number:{}", number_);
	for (std::string str = std::to_string(number_); char c : str)
	{
		if ('0' <= c && c <= '9')
		{
			Number num{ c - '0' };
			DrawNumber(num);
		}
	}
	LOGFLN("");
}

void NumberPlate::Release()
{
}

void NumberPlate::DrawNumber(const Number _number)
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
	float widthPixF{ static_cast<float>(widthPix) };


	Canvas::LayoutConfig config
	{
		Canvas::LayoutConfig{ baseCanvasSize_ }
			.position({ static_cast<float>(currDrawPos_.x), static_cast<float>(currDrawPos_.y) })
			.scale({ static_cast<float>(sizePix_.x), static_cast<float>(sizePix_.y) })
	};

	context.SetRefLayout(&config);

	RectF rect{ widthPixF * static_cast<float>(_number), 0.0f, widthPixF, widthPixF };

	context.DrawImage(
		hNumberImage_,
		0.0f,
		rect);

	// 書いたら横移動
	currDrawPos_.x += sizePix_.x + marginPix_;
}
