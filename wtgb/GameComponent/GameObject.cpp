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
#include "GameSystem/Scriptable.h"

#include "Core/ComponentSetter.h"

wtgb::GameObject::GameObject(const fs::path& _prefabJson) :
	entityId_{ System().Get<ComponentManager>().GetPrevEntity() },
	toDestroy_{ false }
{
	Scriptable& scriptable{ System().Get<Scriptable>() };

	GameObjectBuilder builder{ *this };
	scriptable.LoadPrefabFromJson(_prefabJson, builder);

	// TODO: 重複している
	System().Get<CPGameObject>().Add(entityId_, this);
}


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

	// TODO: 重複している
	System().Get<CPGameObject>().Add(entityId_, this);
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
	System().Get<CPGameObjectProperty>().ForEach([&_name, &foundEntityId](GameObjectProperty& _gameObjectProperty) -> bool
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

bool wtgb::GameObject::FindGameObjects(
	const std::string& _name,
	std::vector<GameObject*>* _pFoundGameObjects)
{
	std::vector<EntityId> foundEntityIds{};
	System().Get<CPGameObjectProperty>().ForEach([&_name, _pFoundGameObjects, &foundEntityIds](GameObjectProperty& _gameObjectProperty) -> bool
		{
			if (_gameObjectProperty.GetName() == _name)
			{
				EntityId foundEntityId = _gameObjectProperty.GetEntityId();
				if (foundEntityId != INVALID_ENTITY)
				{
					if (_pFoundGameObjects == nullptr)
					{  // もし見つけたゲームオブジェクト格納先が無いなら
						return true;  // 見つかった時点でtrueを返す
					}
					foundEntityIds.push_back(foundEntityId);
				}
			}
		});

	if (_pFoundGameObjects == nullptr)
	{  // もし見つけたゲームオブジェクト格納先が無いなら
		return false;  // 見つかった時点で回帰しているので false を返す
	}
	
	_pFoundGameObjects->clear();
	for (EntityId foundEntityId : foundEntityIds)
	{
		GameObject* pGameObject{ System().Get<CPGameObject>().Get(foundEntityId) };
		
		if (pGameObject)
		{
			_pFoundGameObjects->push_back(pGameObject);
		}
	}
	return _pFoundGameObjects->size() > 0;
}
