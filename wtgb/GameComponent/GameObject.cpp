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
	entityId_{ System().Get<ComponentManager>().GetPrevEntity() },
	toDestroy_{ false }
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

wtgb::GameObject* wtgb::GameObject::FindGameObject(const EntityId _entityId)
{
	return System().Get<CPGameObject>().Get(_entityId);
}

wtgb::GameObject* wtgb::GameObject::FindGameObject(const std::string& _name)
{
	wtgb::EntityId foundEntityId{ INVALID_ENTITY };
	System().Get<CPGameObjectProperty>().ForEach([&_name, &foundEntityId](GameObjectProperty& _gameObjectProperty)
		{
			if (_gameObjectProperty.GetName() == _name)
			{
				foundEntityId = _gameObjectProperty.GetEntityId();
			}
		});

	if (foundEntityId == INVALID_ENTITY)
	{
		return nullptr;  // 名前で見つからなければ nullptr 返す
	}
	// 名前で見つかったなら取得してくる
	return System().Get<CPGameObject>().Get(foundEntityId);
}
