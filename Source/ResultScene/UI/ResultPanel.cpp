#include "ResultPanel.h"
#include "UI/DragCircle.h"

ResultPanel::ResultPanel(const EntityId _dragCircle) :
	GameObject{ "Result/ResultPanel.json" },
	baseCanvasSize_{},
	panelImageFile_{},
	dragCircle_{ _dragCircle },
	animOffsetY_{}
{
}

ResultPanel::~ResultPanel()
{
}

void ResultPanel::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());

	hPanelImage_ = System().Get<ResourceSystem>().LoadTexture(panelImageFile_);

	// 掴む円
	DragCircle* pDragCircle{ dynamic_cast<DragCircle*>(FindGameObject(dragCircle_)) };
	pDragCircle->SetRadius(dragCircleSizePix_);
	pDragCircle->SetBaseCanvasSize(baseCanvasSize_);
	pDragCircle->SetPosition(dragCirclePositionDown_);
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

	DragCircle* pDragCircle{ dynamic_cast<DragCircle*>(FindGameObject(dragCircle_)) };

	if (pDragCircle && pDragCircle->IsDrag())
	{
		// 掴んだ分加算する
		Vector2Int displacement{ pDragCircle->GetDisplacement() };
		moveRatio_ += static_cast<float>(-displacement.y) / screenSize.y;
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

	LOGFLN("moveRatio{}", moveRatio_);

	if (pDragCircle)
	{
		// TODO: ボタンドラッグ位置を確定させる
		isDrag_ = pDragCircle->IsDrag();
		//Mathf::Lerp()
		//pDragCircle->SetPosition({ 430 + OFFSET_X, static_cast<int>((screenSize.y / 1.3f) * (1.0f - moveRatio_)) });
	}

	Vector2Int size = pTexture->GetImageSizePix();

	Canvas::LayoutConfig config
	{
		Canvas::LayoutConfig{ baseCanvasSize_ }
			.position({ 0.0f, animOffsetY_ })
			.scale(size)
			.order(100)
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
	_json.at("panelImageFile").get_to(panelImageFile_);
	_json.at("dragCirclePositionDown").get_to(dragCirclePositionDown_);
	_json.at("dragCirclePositionUp").get_to(dragCirclePositionUp_);
	_json.at("dragCircleSizePix").get_to(dragCircleSizePix_);
}
