#include "pch\pch.h"
#include "CPGameObject.h"

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
	ForEach([](GameObject*& _pGameObject)
		{
			if (_pGameObject)
			{
				_pGameObject->Update();
			}
		});
}

void wtgb::CPGameObject::End()
{
	ForEach([](GameObject* _pGameObject)
		{
			if (_pGameObject)
			{
				SAFE_DELETE(_pGameObject);
			}
		});
}

const wtgb::EntityId wtgb::CPGameObject::GetEntityId(const size_t _index) const
{
	return at(_index)->entityId_;
}

void wtgb::CPGameObject::Draw() const
{
	ForEach([](GameObject* _pGameObject)
		{
			if (_pGameObject)
			{
				_pGameObject->Draw();
			}
		});
}
