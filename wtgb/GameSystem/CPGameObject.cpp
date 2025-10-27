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
}

void wtgb::CPGameObject::Update()
{
	for (auto& gameObject : *this)
	{
		gameObject->Update();
	}
}
