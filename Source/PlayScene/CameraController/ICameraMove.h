#pragma once
#include <wtgb.h>

/// <summary>
/// カメラ移動方法のインタフェース
/// </summary>
class ICameraMove
{
public:
	/// <summary>
	/// ゲームオブジェクトの参照
	/// </summary>
	struct GameObjectReference
	{
		GameObjectReference(
			ViewerCached& _system,
			EntityId _self,
			EntityId _dragArrowAxis,
			EntityId _dragArrow
		) :
			system{ _system },
			self{ _self },
			dragArrowAxis{ _dragArrowAxis },
			dragArrow{ _dragArrow }
		{}

		ViewerCached& system;    // システムアクセス用
		EntityId self;           // カメラ自身
		EntityId dragArrowAxis;  // drag矢印の軸
		EntityId dragArrow;      // drag矢印本体
	};

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
