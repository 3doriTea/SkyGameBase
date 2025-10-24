#include "pch\pch.h"
#include "GameObject.h"
#include "Core/GameObjectBuilder.h"

#include "Transform.h"
#include "GameObjectProperty.h"

wtgb::GameObject::GameObject(std::function<void(GameObjectBuilder&)> _callback) :
	entityId_{ wtgb::INVALIED_ID },
	pCachedSystem_{ nullptr }
{
	GameObjectBuilder builder{ *this };
	_callback(builder);
}

wtgb::GameObjectProperty& wtgb::GameObject::Property()
{
}

wtgb::Transform& wtgb::GameObject::Transform()
{
	
}

wtgb::ViewerCached& wtgb::GameObject::System() const
{
	assert(pCachedSystem_ && "システムのcacheがない状態でアクセスできない");

	return *pCachedSystem_;
}
