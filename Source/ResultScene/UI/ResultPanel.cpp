#include "ResultPanel.h"
#include "../ResultScene.h"
#include "DragPoint.h"
#include "TitleScene/TitleScene.h"
#include "UI/StringPlate.h"
#include "../../Systems/ScoreManager.h"
#include "../../FaderController.h"


ResultPanel::ResultPanel(const EntityId _faderController) :
	GameObject{ "Result/ResultPanel.json" },
	baseCanvasSize_{},
	panelImageFileResult_{},
	panelImageFileFailed_{},
	dragPoint_{ INVALID_ENTITY },
	animOffsetY_{},
	stringPlate_{ INVALID_ENTITY, INVALID_ENTITY, INVALID_ENTITY },
	scoreFontSize_{},
	dragCircleSizePix_{},
	hPanelImage_{ INVALID_HANDLE },
	isDrag_{ false },
	moveRatio_{},
	toTitleTime_{},
	isShowResult_{},
	faderController_{ _faderController }
{
}

ResultPanel::~ResultPanel()
{
}

void ResultPanel::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());
	Vector2Int screenSize{ System().Get<GameWindow>().GetMainWindowSize() };

	FaderController* pFaderController{ FindGameObject<FaderController>(faderController_) };
	wassert(pFaderController && "フェーダコントローラが見つからなかった");
	if (pFaderController)
	{
		System().Get<Alarm>().Add([this, pFaderController]
			{
				pFaderController->Hide([this]
					{
						System().Get<SceneManager>().Move<TitleScene>();
					});
			},
			toTitleTime_);
	}

	ResultScene* pResultScene{ GetScene<ResultScene>() };
	wassert(pResultScene && "結果シーンの取得に失敗");
	if (pResultScene == nullptr)
	{
		return;  // 結果シーンの取得に失敗すると何もできない
	}

	if (System().Get<ScoreManager>().IsFailedGoal())
	{
		hPanelImage_ = System().Get<ResourceSystem>().LoadTexture(panelImageFileFailed_);
		isShowResult_ = false;  // 結果表示は行わない
		return;  // 失敗時の表示のみでほかは非表示
	}
	else  // 通常は結果表示
	{
		hPanelImage_ = System().Get<ResourceSystem>().LoadTexture(panelImageFileResult_);
		isShowResult_ = true;  // 結果表示を行う
	}

	for (GameScore::ScoreType type{}; type < GameScore::ScoreType_Max; type++)
	{
		stringPlate_[type] = pResultScene->Instantiate<StringPlate>(
			numberFontImagePath_);
	}

	CoordinateTransformer transformer{ screenSize, baseCanvasSize_ };
	dragPoint_ = pResultScene->Instantiate<DragPoint>(transformer);

	// 掴む円
	DragPoint* pDragPoint{ dynamic_cast<DragPoint*>(FindGameObject(dragPoint_)) };
	assert(pDragPoint);
	pDragPoint->SetRadius(dragCircleSizePix_);
	pDragPoint->SetPosition(dragCirclePositionDown_);
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

	if (isShowResult_)  // 結果表示があるなら
	{
		DragPoint* pDragPoint{ FindGameObject<DragPoint>(dragPoint_) };
		wassert(pDragPoint);

		StringPlate* pStringPlate[GameScore::ScoreType_Max]{};
		for (GameScore::ScoreType type{}; type < GameScore::ScoreType_Max; type++)
		{
			pStringPlate[type] = FindGameObject<StringPlate>(stringPlate_[type]);
			wassert(pStringPlate[type]);

			if (pStringPlate[type])
			{
				pStringPlate[type]->SetPosition(scoreTextPosition_[type]);
				pStringPlate[type]->SetSize(scoreFontSize_);
			}
		}

		System().Get<ScoreManager>().Ref([pStringPlate](GameScore& _score)
			{
				pStringPlate[GameScore::ScoreType_PresentCount]->SetString(
					std::format("{}p", _score.presentCount));
				pStringPlate[GameScore::ScoreType_AllyCount]->SetString(
					std::format("{}h", _score.allyCount));
				pStringPlate[GameScore::ScoreType_TimeDifference]->SetString(
					std::format("{:.7}s", _score.timeDifference));
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
}

void ResultPanel::Release()
{
}

void ResultPanel::OnLoadParam(const json& _json)
{
	_json.at("baseCanvasSize").get_to(baseCanvasSize_);
	_json.at("panelImageFileResult").get_to(panelImageFileResult_);
	_json.at("panelImageFileFailed").get_to(panelImageFileFailed_);
	_json.at("dragCirclePositionDown").get_to(dragCirclePositionDown_);
	_json.at("dragCirclePositionUp").get_to(dragCirclePositionUp_);
	_json.at("dragCircleSizePix").get_to(dragCircleSizePix_);
	_json.at("toTitleMoveTime").get_to(toTitleTime_);
	_json.at("numberFontImagePath").get_to(numberFontImagePath_);
	_json.at("scoreFontSize").get_to(scoreFontSize_);
	
	for (GameScore::ScoreType type{}; type < GameScore::ScoreType_Max; type++)
	{
		_json.at("scoreTextPosition").at(type).get_to(scoreTextPosition_[type]);
	}
}
