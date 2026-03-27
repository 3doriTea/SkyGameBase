#include "TitleText.h"
#include "TitleNeco.h"


TitleText::TitleText(const EntityId _titleNeco) :
	GameObject{ "Title/TitleText.json" },
	titleNeco_{ _titleNeco },
	hImage_{ INVALID_HANDLE },
	beginPosition_{},
	endPosition_{},
	imageSize_{}
{
}

TitleText::~TitleText()
{
}

void TitleText::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());
}

void TitleText::Update()
{
	const Canvas::Context& context{ System().Get<Canvas>().GetContext() };

	UI::LayoutConfig config{ Vector2Int{ 1920, 1080 } };
	context.SetRefLayout(&config);

	TitleNeco* pTitleNeco{ FindGameObject<TitleNeco>(titleNeco_) };
	wassert(pTitleNeco && "タイトルネコが見つからない");
	if (pTitleNeco)
	{
		// ドラッグ中の移動レート
		const float MOVE_RATIO{ pTitleNeco->GetMoveRaito() };

		Vector2 position
		{
			Mathf::Lerp(
				beginPosition_,
				endPosition_,
				Ease::InBack(MOVE_RATIO))
		};
		
		config.position(position);
		config.scale(imageSize_);

		context.DrawImage(hImage_);
	}
}

void TitleText::Release()
{
}

void TitleText::OnLoadParam(const json& _json)
{
	ResourceSystem& rc{ System().Get<ResourceSystem>() };

	hImage_ = rc.LoadTexture(
		SafeGet<std::string>(_json, "imageFilePath"));

	imageSize_ = rc.GetTexture(hImage_)->GetImageSizePix();

	beginPosition_ = SafeGet<Vector2>(_json, "beginPosition");
	endPosition_ = SafeGet<Vector2>(_json, "endPosition");
}
