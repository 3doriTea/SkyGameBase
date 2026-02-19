#include "SpeedMessage.h"
#include "../ISpeedController.h"

SpeedMessage::SpeedMessage(const EntityId _speedController) :
	GameObject{ "Play/UI/SpeedMessage.json" },
	speedController_{ _speedController },
	hTextureTooFast_{},
	hTextureTooSlow_{},
	imageFileTooFast_{},
	imageFileTooSlow_{}
{
}

SpeedMessage::~SpeedMessage()
{
}

void SpeedMessage::OnLoadParam(const json& _json)
{
	imageFileTooFast_ = SafeGet<std::string>(_json, "imageFileTooFast");
	imageFileTooSlow_ = SafeGet<std::string>(_json, "imageFileTooSlow");
}

void SpeedMessage::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());

	ResourceSystem& rsrcSystem{ System().Get<ResourceSystem>() };

	hTextureTooFast_ = rsrcSystem.LoadTexture(imageFileTooFast_);
	wassert(hTextureTooFast_ != INVALID_HANDLE
		&& "imageFileTooFastの読み込み失敗");
	
	hTextureTooSlow_ = rsrcSystem.LoadTexture(imageFileTooSlow_);
	wassert(hTextureTooSlow_ != INVALID_HANDLE
		&& "imageFileTooSlowの読み込み失敗");

	Vector2Int tooFastImageSize{ rsrcSystem.GetTexture(hTextureTooFast_)->GetImageSizePix() };
	Vector2Int tooSlowImageSize{ rsrcSystem.GetTexture(hTextureTooSlow_)->GetImageSizePix() };

	wassert(tooFastImageSize == tooSlowImageSize
		&& "速すぎ遅すぎの画像サイズが不一致");

	// 画像サイズを入れておく
	imageSize_ = tooFastImageSize;
}

void SpeedMessage::Update()
{
	ISpeedController* pSpeedController{ FindGameObject<ISpeedController>(speedController_) };
	wassert(pSpeedController && "speedControllerが見つからなかった！");

	const Canvas::Context& CONTEXT{ System().Get<Canvas>().GetContext() };

	UI::LayoutConfig config{};
	config
		.position(Vector2Int::Zero())
		.scale(imageSize_);

	CONTEXT.SetRefLayout(&config);


	if (pSpeedController)
	{
		SpeedType speedType{ pSpeedController->GetSpeedType() };

		// 各スピード状態に応じて表示する
		switch (speedType)
		{
		case SpeedType::TooSlow:  // 遅すぎ
			CONTEXT.DrawImage(hTextureTooSlow_);
			break;
		case SpeedType::Excissive:  // 速すぎ
			CONTEXT.DrawImage(hTextureTooFast_);
			break;
		// 他は無視
		case SpeedType::Stop:
		case SpeedType::Good:
			break;
		default:
			wassert("未実装のSpeedTypeが指定されました。");
			break;
		}
	}
}

void SpeedMessage::Release()
{
}
