#include "pch\pch.h"
#include "CPGameObjectProperty.h"

wtgb::CPGameObjectProperty::CPGameObjectProperty()
{
}

wtgb::CPGameObjectProperty::~CPGameObjectProperty()
{
}

void wtgb::CPGameObjectProperty::Init()
{
}

void wtgb::CPGameObjectProperty::Update()
{
}

void wtgb::CPGameObjectProperty::SetFamily(const EntityId _parent, const EntityId _child)
{
	if (_parent == INVALID_ENTITY && _child == INVALID_ENTITY)
	{
		return;  // 無意味なので無視
	}

	if (_parent == INVALID_ENTITY)
	{
		// 親を切り離す
		at(_child).parent_ = INVALID_ENTITY;
	}

	if (_child == INVALID_ENTITY)
	{
		throw "子の指定がありません";
		// 子を切り離す
		//at(_parent).RemoveAllChild();
	}

	if (at(_child).parent_ != INVALID_ENTITY)
	{
		// 親がいるなら切り離す
		SetFamily(INVALID_ENTITY, _child);
	}
	at(_child).parent_ = _child;
}
