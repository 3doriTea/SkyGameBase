#include "pch\pch.h"
#include "CPGameObject.h"
#include "GameSystem/ComponentManager.h"
#include "WTGBAssert.h"
#include "CPGameObjectProperty.h"

wtgb::CPGameObject::CPGameObject()
{
}

wtgb::CPGameObject::~CPGameObject()
{
}

void wtgb::CPGameObject::Init()
{
	GameObject::pCachedSystem_ = &System();
}

void wtgb::CPGameObject::Update()
{
	ComponentManager& componentManager{ System().Get<ComponentManager>() };

	ForEach([](const std::shared_ptr<GameObject>& _pGameObject) -> BreakToken
		{
			if (_pGameObject)
			{
				_pGameObject.get()->Update();
			}
			return {};
		});

	ForEach([&componentManager](const std::shared_ptr<GameObject>& _pGameObject) -> BreakToken
		{
			if (_pGameObject.get()->IsToDestroy())
			{
				componentManager.RemoveEntity(_pGameObject.get()->entityId_);
			}
			return {};
		});
}

void wtgb::CPGameObject::End()
{
	ForEach([](const std::shared_ptr<GameObject>& _pGameObject) -> BreakToken
		{
			if (_pGameObject)
			{
				_pGameObject.get()->End();
			}
			return {};
		});
}

const wtgb::EntityId wtgb::CPGameObject::GetEntityId(const size_t _index) const
{
	GameObject* pGameObject{ at(_index).get() };
	wassert(pGameObject && "ゲームオブジェクトがまだ作られていない");
	if (pGameObject)
	{
		return pGameObject->entityId_;
	}
	else
	{
		return INVALID_ENTITY;
	}
}

wtgb::GameObject* wtgb::CPGameObject::FindGameObject(const std::string_view _name)
{
	EntityId foundEntityId{ System().Get<CPGameObjectProperty>().FindEntityByName(_name) };
	if (foundEntityId == INVALID_ENTITY)
	{
		return nullptr;
	}
	else
	{
		return at(foundEntityId).get();
	}
}

wtgb::GameObject* wtgb::CPGameObject::FindGameObject(const EntityId _entityId)
{
	return at(_entityId).get();
}

void wtgb::CPGameObject::Draw() const
{
	ForEach([](const std::shared_ptr<GameObject>& _pGameObject) -> BreakToken
		{
			if (_pGameObject)
			{
				_pGameObject.get()->Draw();
			}
			return {};
		});
}
