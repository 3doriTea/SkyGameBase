#pragma once
#include <wtgb.h>

/// <summary>
/// カメラ移動方法のインタフェース
/// </summary>
class ICameraMove
{
public:
	ICameraMove() {}
	virtual ~ICameraMove() {}

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Start() = 0;
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_system">システムアクセス用キャッシュ</param>
	/// <param name="_entityId">更新するエンティティId</param>
	virtual void Update(ViewerCached& _system, const EntityId _entityId) = 0;
	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void End() = 0;
};
