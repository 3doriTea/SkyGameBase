#include "pch\pch.h"
#include "CPGameObject.h"
#include "GameSystem/ComponentManager.h"
#include "WTGBAssert.h"

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

	ForEach([](GameObject*& _pGameObject) -> BreakToken
		{
			if (_pGameObject)
			{
				_pGameObject->Update();
			}
			return {};
		});

	ForEach([&componentManager](GameObject*& _pGameObject) -> BreakToken
		{
			if (_pGameObject->IsToDestroy())
			{
				componentManager.RemoveEntity(_pGameObject->entityId_);
			}
			return {};
		});
}

void wtgb::CPGameObject::End()
{
	ForEach([](GameObject* _pGameObject) -> BreakToken
		{
			if (_pGameObject)
			{
				_pGameObject->End();
			}
			return {};
		});
}

const wtgb::EntityId wtgb::CPGameObject::GetEntityId(const size_t _index) const
{
	GameObject* pGameObject{ at(_index) };
	wassert(pGameObject && "ゲームオブジェクトがまだ作られていない");
	return pGameObject->entityId_;
}

void wtgb::CPGameObject::Draw() const
{
	ForEach([](GameObject* _pGameObject) -> BreakToken
		{
			if (_pGameObject)
			{
				_pGameObject->Draw();
			}
			return {};
		});
}
