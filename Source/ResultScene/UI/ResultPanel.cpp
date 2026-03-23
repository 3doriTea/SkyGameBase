#include "ResultPanel.h"
#include "../ResultScene.h"
#include "DragPoint.h"
#include "TitleScene/TitleScene.h"
#include "UI/NumberPlate.h"
#include "../../Systems/ScoreManager.h"


ResultPanel::ResultPanel() :
	GameObject{ "Result/ResultPanel.json" },
	baseCanvasSize_{},
	panelImageFile_{},
	dragPoint_{ INVALID_ENTITY },
	animOffsetY_{},
	numberPlate_{ INVALID_ENTITY, INVALID_ENTITY, INVALID_ENTITY },
	scoreFontSize_{}
{
}

ResultPanel::~ResultPanel()
{
}

void ResultPanel::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());
	Vector2Int screenSize{ System().Get<GameWindow>().GetMainWindowSize() };

	GameScene* pGameScene{ GetScene() };
	if (pGameScene)
	{
		for (GameScore::ScoreType type{}; type < GameScore::ScoreType_Max; type++)
		{
			numberPlate_[type] = pGameScene->Instantiate<NumberPlate>(
				numberFontImagePath_);
		}
	}

	ResultScene* pResultScene{ GetScene<ResultScene>() };
	wassert(pResultScene && "結果シーンの取得に失敗");
	if (pResultScene == nullptr)
	{
		return;  // 結果シーンの取得に失敗すると何もできない
	}

	hPanelImage_ = System().Get<ResourceSystem>().LoadTexture(panelImageFile_);

	CoordinateTransformer transformer{ screenSize, baseCanvasSize_ };
	dragPoint_ = pResultScene->Instantiate<DragPoint>(transformer);

	// 掴む円
	DragPoint* pDragPoint{ dynamic_cast<DragPoint*>(FindGameObject(dragPoint_)) };
	assert(pDragPoint);
	pDragPoint->SetRadius(dragCircleSizePix_);
	pDragPoint->SetPosition(dragCirclePositionDown_);

	System().Get<Alarm>().Add([this]
		{
			System().Get<SceneManager>().Move<TitleScene>();
		},
		toTitleTime_);
}

void ResultPanel::Update()
{
	Cursor& cursor{ System().Get<Cursor>() };

	const float dt{ System().Get<GameTime>().GetDeltaTime() };
	const Input::InputGetter& input{ System().Get<Input>().Getter() };
	const Canvas::Context& context{ System().Get<Canvas>().GetContext() };
	const Vector2Int screenSizeInt{ System().Get<GameWindow>().GetMainWindowSize() };
	const Vector2 screenSize{ static_cast<float>(screenSizeInt.x), static_cast<float>(screenSizeInt.y) };

	Texture* pTexture{ System().Get<ResourceSystem>().GetTexture(hPanelImage_) };
	wassert(pTexture && "テクスチャの取得に失敗");

	if (pTexture == nullptr)
	{
		return;
	}

	DragPoint* pDragPoint{ FindGameObject<DragPoint>(dragPoint_) };
	wassert(pDragPoint);

	NumberPlate* pNumberPlate[GameScore::ScoreType_Max]{};
	for (GameScore::ScoreType type{}; type < GameScore::ScoreType_Max; type++)
	{
		pNumberPlate[type] = FindGameObject<NumberPlate>(
			numberPlate_[GameScore::ScoreType_PresentCount]);
		wassert(pNumberPlate[type]);

		if (pNumberPlate[type])
		{
			pNumberPlate[type]->SetPosition(scoreTextPosition_[type]);
			pNumberPlate[type]->SetSize(scoreFontSize_);
		}
	}

	System().Get<ScoreManager>().Ref([pNumberPlate](GameScore& _score)
		{
			pNumberPlate[GameScore::ScoreType_PresentCount]->SetNumber(_score.presentCount);
			pNumberPlate[GameScore::ScoreType_AllyCount]->SetNumber(_score.allyCount);
			pNumberPlate[GameScore::ScoreType_TimeDifference]->SetNumber(_score.timeDifference);
		});

	if (pDragPoint && pDragPoint->IsDrag())
	{
		// 掴んだ分加算する
		Vector2Int displacement{ pDragPoint->GetDisplacement() };
		moveRatio_ += static_cast<float>(-displacement.y) / screenSize.y;
		LOGFLN("ドラッグされた{}", moveRatio_);
	}
	else
	{
		// 掴まれていないなら、自動で引篭る
		if (moveRatio_ < 0.5f)
		{
			moveRatio_ -= dt / 3.0f;
		}
		else
		{
			moveRatio_ += dt / 3.0f;
		}
	}
	moveRatio_ = min(max(moveRatio_, 0.0f), 1.0f);


	if (pDragPoint)
	{
		// TODO: ボタンドラッグ位置を確定させる
		isDrag_ = pDragPoint->IsDrag();
		//Mathf::Lerp()
		//pDragPoint->SetPosition({ 430 + OFFSET_X, static_cast<int>((screenSize.y / 1.3f) * (1.0f - moveRatio_)) });
	}

	Vector2Int size = pTexture->GetImageSizePix();

	Canvas::LayoutConfig config
	{
		Canvas::LayoutConfig{ baseCanvasSize_ }
			.position({ 0.0f, animOffsetY_ })
			.scale(size)
			.order(1000)
	};

	context.SetRefLayout(&config);

	context.DrawImage(hPanelImage_);

	/*Canvas::LayoutConfig{}
		.position({})*/
}

void ResultPanel::Release()
{
}

void ResultPanel::OnLoadParam(const json& _json)
{
	_json.at("baseCanvasSize").get_to(baseCanvasSize_);
	_json.at("panelImageFile").get_to(panelImageFile_);
	_json.at("dragCirclePositionDown").get_to(dragCirclePositionDown_);
	_json.at("dragCirclePositionUp").get_to(dragCirclePositionUp_);
	_json.at("dragCircleSizePix").get_to(dragCircleSizePix_);
	_json.at("toTitleMoveTime").get_to(toTitleTime_);
	_json.at("numberFontImagePath").get_to(numberFontImagePath_);
	_json.at("scoreFontSize").get_to(scoreFontSize_);
	
	for (GameScore::ScoreType type{}; type < GameScore::ScoreType_Max; type++)
	{
		std::string tttttttt = _json.at("scoreTextPosition").dump();

		_json.at("scoreTextPosition").at(type).get_to(scoreTextPosition_[type]);
	}
}
