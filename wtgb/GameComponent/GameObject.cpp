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
#include "GameSystem/CPGameObject.h"

#include "WTGBAssert.h"

#include "Core/ComponentSetter.h"

wtgb::GameObject::GameObject(const fs::path& _prefabJson) :
	entityId_{ System().Get<ComponentManager>().GetPrevEntity() },
	toDestroy_{ false }
{
	// TODO: 重複している
	System().Get<CPGameObject>().Add(entityId_, this);

	Scriptable& scriptable{ System().Get<Scriptable>() };

	GameObjectBuilder builder{ *this };
	scriptable.LoadPrefabFromJson(_prefabJson, builder);

}


wtgb::GameObject::GameObject() : 
	GameObject{ [](GameObjectBuilder&){} }
{
}

wtgb::GameObject::GameObject(std::function<void(GameObjectBuilder&)> _callback) :
	entityId_{ System().Get<ComponentManager>().GetPrevEntity() },
	toDestroy_{ false }
{
	System().Get<CPGameObject>().Add(entityId_, this);
	
	GameObjectBuilder builder{ *this };
	_callback(builder);

	// TODO: 重複している
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
	wtgb::EntityId foundEntityId{ System().Get<CPGameObjectProperty>().FindEntityByName(_name) };
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
	bool isFound{ false };

	System().Get<CPGameObjectProperty>().ForEach(
		[&_name, _pFoundGameObjects, &foundEntityIds, &isFound](GameObjectProperty& _gameObjectProperty) -> BreakToken
		{
			if (_gameObjectProperty.GetName() == _name)
			{
				EntityId foundEntityId = _gameObjectProperty.GetEntityId();
				if (foundEntityId != INVALID_ENTITY)
				{
					if (_pFoundGameObjects == nullptr)
					{  // もし見つけたゲームオブジェクト格納先が無いなら
						isFound = true;
						return true;  // 見つかった時点で止める
					}
					foundEntityIds.push_back(foundEntityId);
				}
			}

			return false;
		});

	if (_pFoundGameObjects == nullptr)
	{  // もし見つけたゲームオブジェクト格納先が無いなら
		return isFound;  // 見つかったかどうかを即返す
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
