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
