#include "pch\pch.h"
#include "Cursor.h"
#include "GameSystem/GameWindow.h"
#include "GameSystem/Debug.h"

wtgb::Cursor::Cursor() :
	system_{ nullptr },
	isCenterLock_{ false },
	previousPosition_{ -1, -1 },
	isIgnoreMoveFlag_{ true },
	clientSize_{ Vector2Int::Zero() },
	updater_{ this },
	isShow_{ true }
{
}

wtgb::Cursor::~Cursor()
{
}

wtgb::Result wtgb::Cursor::Init(const ViewerInit& _viewer)
{
	system_ = _viewer.GetCache();
	return Result::Code::Ok;
}

void wtgb::Cursor::Update(const ViewerUpdate& _system)
{
	frameMove_ = frameMoveDelta_;
	frameMoveDelta_ = Vector2Int::Zero();
}

void wtgb::Cursor::End()
{
	if (!isShow_)
	{
		ShowCursor(true);
	}
}

void wtgb::Cursor::SetCenterLock(const bool _isCenterLock)
{
	isCenterLock_ = _isCenterLock;
}

void wtgb::Cursor::SetShow(const bool _isShow)
{
	ShowCursor(_isShow);
	isShow_ = _isShow;
}

wtgb::Vector2Int wtgb::Cursor::GetPosition() const
{
	return previousPosition_;
}

void wtgb::Cursor::SetPositionCenter()
{
	GameWindow& gameWindow{ System().Get<GameWindow>() };

	POINT center  // ウィンドウクライアント内の中心座標
	{
		gameWindow.GetMainWindowSize().x / 2,
		gameWindow.GetMainWindowSize().y / 2,
	};
	Vector2Int moveDiff{ Vector2Int{ center.x - previousPosition_.x, center.y - previousPosition_.y } };
	frameMoveDelta_ -= moveDiff;
	
	// スクリーン内の座標へ変換
	ClientToScreen(gameWindow.GetMainWindowHandle(), &center);
	// カーソル座標をセット
	SetCursorPos(center.x, center.y);
}

void wtgb::Cursor::CursorUpdater::UpdatePosition(const Vector2Int& _clientPos)
{
	Cursor& cursor{ *GetAccess() };

	if (cursor.isIgnoreMoveFlag_)
	{
		// 無視するフラグが立っているなら、移動量を加算せずに下す
		cursor.isIgnoreMoveFlag_ = false;
	}
	else
	{
		// 移動量を加算する
		cursor.frameMoveDelta_ += _clientPos - cursor.previousPosition_;

		if (cursor.isCenterLock_)
		{
			// 中心ロックモードなら中心にカーソルロック
			cursor.SetPositionCenter();
		}
	}

	// 前回のカーソル座標を更新
	cursor.previousPosition_ = _clientPos;
}
