#include "pch\pch.h"
#include "GameObjectProperty.h"
#include "WTGBAssert.h"

wtgb::GameObjectProperty::GameObjectProperty()
{
}

wtgb::GameObjectProperty::~GameObjectProperty()
{
}

void wtgb::GameObjectProperty::SetName(const std::string& _name)
{
	if (_name.size() > NAME_SIZE)
	{
		memcpy(reinterpret_cast<void*>(name_), _name.data(), NAME_SIZE);
	}
	else
	{
		memset(reinterpret_cast<void*>(name_), 0, NAME_SIZE);
		memcpy(reinterpret_cast<void*>(name_), _name.data(), _name.size());
	}
}

void wtgb::GameObjectProperty::SetParent(const EntityId _parent)
{
}

void wtgb::GameObjectProperty::CountChilds() const
{
}

void wtgb::GameObjectProperty::SetParent(const EntityId _parent)
{
	//system_.Get<CPGameObjectProperty>().
}

void wtgb::GameObjectProperty::AddChild(const EntityId _entityId)
{
	for (auto itr = childs_.begin(); itr != childs_.end(); itr++)
	{
		if ((*itr) == INVALID_ENTITY)
		{
			*itr = _entityId;
			return;  // 空の場所を見つけたらそこに入れて回帰
		}
	}
	wassert(false && "子を追加できるキャパシティが必要");
	throw "子の数の上限に達しました";
}

void wtgb::GameObjectProperty::RemoveChild(const EntityId _entityId)
{
	for (auto itr = childs_.begin(); itr != childs_.end(); itr++)
	{
		if ((*itr) == _entityId)
		{
			(*itr) = INVALID_ENTITY;
			return;
		}
	}

	wassert(false && "削除予定の子が見つからなかった");
}

void wtgb::GameObjectProperty::RemoveAllChild()
{
	for (auto itr = childs_.begin(); itr != childs_.end(); itr++)
	{
		(*itr) == INVALID_ENTITY;
	}
}
