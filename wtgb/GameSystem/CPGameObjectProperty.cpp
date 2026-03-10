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

	// まず親がいるなら関係を打ち切る
	if (at(_child).parent_ != INVALID_ENTITY)
	{
		at(at(_child).parent_).RemoveChild(_child);
		at(_child).parent_ = INVALID_ENTITY;
	}

	if (_parent == INVALID_ENTITY)
	{
		// 親無しにするならそのまま
	}
	else
	{
		// 親に子を追加し、子は親を設定する
		at(_parent).AddChild(_child);
		at(_child).parent_ = _parent;
	}
}

const wtgb::EntityId wtgb::CPGameObjectProperty::GetEntityId(const GameObjectProperty* _p) const
{
	size_t index{ static_cast<size_t>(_p - DataBegin()) };
	return System().Get<CPGameObject>().GetEntityId(index);
}

const wtgb::EntityId wtgb::CPGameObjectProperty::FindEntityByName(const std::string_view _name)
{
	wtgb::EntityId foundEntityId{ INVALID_ENTITY };
	ForEach(
		[&_name, &foundEntityId](GameObjectProperty& _gameObjectProperty) -> BreakToken
		{
			if (_gameObjectProperty.GetName() == _name)
			{
				foundEntityId = _gameObjectProperty.GetEntityId();
				return true;  // 見つかったからループを止める
			}
			return false;
		});

	return foundEntityId;
}
