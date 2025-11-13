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
	for (auto& gameObject : *this)
	{
		if (gameObject)
		{
			SAFE_DELETE(gameObject);
		}
	}
}

wtgb::EntityId wtgb::CPGameObject::GetEntityId(const size_t _index)
{
	return at(_index)->entityId_;
}

void wtgb::CPGameObject::Draw() const
{
	ForEach([](const GameObject*& _pGameObject)
		{
			if (_pGameObject)
			{
				_pGameObject->Draw();
			}
		});
}
