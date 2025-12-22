#include "pch\pch.h"
#include "CPGameObjectProperty.h"
#include "CPGameObject.h"

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
		assert(false && "親子ともに無効な値が指定された");
		return;  // 無意味なので無視
	}

	if (_child == INVALID_ENTITY)
	{
		// MEMO: 子の指定が無効値の場合、すべての子を切り離すようにしていたが、危険なため例外スローにした。
		assert(false && "子が無効な値");
		throw "子の指定がありません";
		// 子を切り離す
		//at(_parent).RemoveAllChild();
	}

	auto pro = at(_child);
	if (at(_child).parent_ != INVALID_ENTITY)
	{
		// 既に親がいるなら切り離す
		at(at(_child).parent_).RemoveChild(_child);
		at(_child).parent_ = INVALID_ENTITY;
	}

	// 親を消したいなら
	if (_parent == INVALID_ENTITY)
	{
		// 既にできているため回帰
		return;
	}
	else  // 親を交換したいなら
	{
		// 親子関係を結ぶ
		at(_child).parent_ = _parent;
		at(_parent).AddChild(_child);
	}
}

const wtgb::EntityId wtgb::CPGameObjectProperty::GetEntityId(const GameObjectProperty* _p) const
{
	size_t index{ static_cast<size_t>(_p - DataBegin()) };
	return System().Get<CPGameObject>().GetEntityId(index);
}
