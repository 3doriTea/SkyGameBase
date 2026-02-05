#include "GoalGround.h"

GoalGround::GoalGround(const Vector3& _position) :
	GameObject{ "Play/GoalGround.json" }
{
	Transform().SetPosition(_position);
}

GoalGround::~GoalGround()
{
}

void GoalGround::Init()
{
}

void GoalGround::Update()
{
}

void GoalGround::Release()
{
}
