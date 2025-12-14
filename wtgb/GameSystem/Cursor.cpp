#include "pch\pch.h"
#include "Cursor.h"
#include "GameSystem/GameWindow.h"
#include "GameSystem/Debug.h"

wtgb::Cursor::Cursor() :
	system_{ nullptr },
	previousPosition_{ -1, -1 },
	isIgnoreMoveFlag_{ true },
	updater_{ this },
	isShow_{ true },
	isLock_{ false },
	lockPosition_{ Vector2Int::Zero() }
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

void wtgb::Cursor::SetLock(const bool _isLock, const Vector2Int _lockPosition)
{
	isLock_ = _isLock;
	lockPosition_ = _lockPosition;
}

void wtgb::Cursor::SetCenterLock(const bool _isCenterLock)
{
	GameWindow& gameWindow{ System().Get<GameWindow>() };

	SetLock(_isCenterLock, gameWindow.GetMainWindowSize() / 2);
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

	// ウィンドウクライアント内の中心座標
	SetPosition(gameWindow.GetMainWindowSize() / 2);
}

void wtgb::Cursor::SetPosition(const Vector2Int _position)
{
	GameWindow& gameWindow{ System().Get<GameWindow>() };

	POINT position  // ウィンドウクライアント内の中心座標
	{
		_position.x, _position.y
	};
	Vector2Int moveDiff{ Vector2Int{ position.x - previousPosition_.x, position.y - previousPosition_.y } };
	frameMoveDelta_ -= moveDiff;

	// スクリーン内の座標へ変換
	ClientToScreen(gameWindow.GetMainWindowHandle(), &position);
	// カーソル座標をセット
	SetCursorPos(position.x, position.y);
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

		//LOGFLN("frameMoveDelta:({}, {})", cursor.frameMoveDelta_.x, cursor.frameMoveDelta_.y);

		if (cursor.isLock_)
		{
			// ロックモードならロックする座標へセット
			cursor.SetPosition(cursor.lockPosition_);
		}
	}

	// 前回のカーソル座標を更新
	cursor.previousPosition_ = _clientPos;
}
