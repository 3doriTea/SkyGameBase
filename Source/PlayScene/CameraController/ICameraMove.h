#pragma once
#include <wtgb.h>

/// <summary>
/// カメラ移動方法のインタフェース
/// </summary>
class ICameraMove
{
public:
	using GameObjectReference = std::pair<ViewerCached&, const EntityId>;
public:
	ICameraMove() {}
	virtual ~ICameraMove() {}

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Start(GameObjectReference _ref) = 0;
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name=""></param>
	virtual void Update(GameObjectReference _ref) = 0;
	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void End(GameObjectReference _ref) = 0;
};
