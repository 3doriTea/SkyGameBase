#include "pch\pch.h"
#include "GameObject.h"
#include "Core/GameObjectBuilder.h"
#include "Core/GameScene.h"

#include "Transform.h"
#include "GameSystem/CPTransform.h"
#include "GameObjectProperty.h"
#include "GameSystem/CPGameObjectProperty.h"
//#include "CPTransform.h"
#include "GameSystem/ComponentManager.h"

#include "Core/ComponentSetter.h"

wtgb::GameObject::GameObject() : 
	GameObject{ [](GameObjectBuilder&){} }
{
}

wtgb::GameObject::GameObject(std::function<void(GameObjectBuilder&)> _callback) :
	entityId_{ System().Get<ComponentManager>().GetPrevEntity() }
{
	GameObjectBuilder builder{ *this };
	_callback(builder);
}

wtgb::GameObject::~GameObject()
{
}

wtgb::GameObjectProperty& wtgb::GameObject::Property()
{
	return System().Get<ComponentManager>().Get<GameObjectProperty>(entityId_);
}

wtgb::Transform& wtgb::GameObject::Transform()
{
	return System().Get<ComponentManager>().Get<wtgb::Transform>(entityId_);
}

wtgb::ViewerCached& wtgb::GameObject::System() const
{
	assert(pCachedSystem_ && "システムのcacheがない状態でアクセスできない");

	return *pCachedSystem_;
}

wtgb::ViewerCached* wtgb::GameObject::pCachedSystem_{ nullptr };

void wtgb::GameObject::End()
{
	this->Release();
	delete this;
}
