#include "pch\pch.h"
#include "GameObjectProperty.h"

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
