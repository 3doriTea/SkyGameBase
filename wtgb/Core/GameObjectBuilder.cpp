#include "pch\pch.h"
#include "GameObjectBuilder.h"

wtgb::GameObjectBuilder::GameObjectBuilder(GameObject& _target) :
	target_{ _target }
{
}

wtgb::GameObjectBuilder::~GameObjectBuilder()
{
}

void wtgb::GameObjectBuilder::OnLoadParam(const json& _json)
{
	(&target_)->OnLoadParam(_json);
}
