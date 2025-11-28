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

	virtual void Start() = 0;
	virtual void Update(ViewerCached& _system) = 0;
	virtual void End() = 0;
};
