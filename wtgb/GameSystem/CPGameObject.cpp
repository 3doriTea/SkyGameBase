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
	for (auto& gameObject : *this)
	{
		if (gameObject)
		{
			gameObject->Update();
		}
	}
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
	auto itr{ begin() + _index };
	return (*itr)->entityId_;
}

void wtgb::CPGameObject::Draw() const
{
	for (const auto& gameObject : *this)
	{
		if (gameObject)
		{
			gameObject->Draw();
		}
	}
}
