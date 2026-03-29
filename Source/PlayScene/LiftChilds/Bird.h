#pragma once
#include "LiftChild.h"


/// <summary>
/// リフト追従オブジェクト : 鳥
/// </summary>
class Bird : public LiftChild
{
public:
	Bird(const EntityId _parentLift);
	~Bird() = default;

private:
	ModelHandle hModel_;
};
