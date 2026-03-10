#include "pch\pch.h"
#include "GameObjectProperty.h"
#include "GameSystem/CPGameObjectProperty.h"
#include "GameSystem/CPGameObject.h"
#include "WTGBAssert.h"

wtgb::GameObjectProperty::GameObjectProperty() :
	name_{},
	parent_{ INVALID_ENTITY },
	childsCount_{ 0 },
	childs_{},
	system_{ nullptr },
	self_{ INVALID_ENTITY }
{
}

wtgb::GameObjectProperty::~GameObjectProperty()
{
}

void wtgb::GameObjectProperty::Init(ViewerCached _system)
{
	system_ = _system;
	if (parent_ != INVALID_ENTITY)
	{
		SetParent(parent_);
	}
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

void wtgb::GameObjectProperty::CountChilds() const
{
}

void wtgb::GameObjectProperty::SetParent(const EntityId _parent)
{
	System().Get<CPGameObjectProperty>().SetFamily(_parent, GetEntityId());
}

void wtgb::GameObjectProperty::AddChild(const EntityId _entityId)
{
	for (auto itr = childs_.begin(); itr != childs_.end(); itr++)
	{
		if ((*itr) == INVALID_ENTITY)
		{
			*itr = _entityId;
			childsCount_++;
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
			childsCount_--;
			return;
		}
	}

	//wassert(false && "削除予定の子が見つからなかった");
}

void wtgb::GameObjectProperty::RemoveAllChild()
{
	for (auto itr = childs_.begin(); itr != childs_.end(); itr++)
	{
		(*itr) == INVALID_ENTITY;
		childsCount_--;
	}
}

void wtgb::GameObjectProperty::Update(ViewerCached _system)
{
}

const wtgb::EntityId wtgb::GameObjectProperty::GetEntityId()
{
	ComponentManager& componentManager{ System().Get<ComponentManager>() };
	if (componentManager.IsInvalidId(self_))
	{
		self_ = System().Get<CPGameObjectProperty>().GetEntityId(this);

		if (componentManager.IsInvalidId(self_))
		{
			self_ = System().Get<ComponentManager>().GetPrevEntity();
		}
	}
	return self_;
}
