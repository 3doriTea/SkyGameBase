#include "pch\pch.h"
#include "CPTransform.h"
#include "GameSystem/CPGameObject.h"
#include "GameSystem/CPGameObjectProperty.h"
#include "WTGBAssert.h"


wtgb::CPTransform::CPTransform()
{
}

wtgb::CPTransform::~CPTransform()
{
}

void wtgb::CPTransform::Init()
{
}

void wtgb::CPTransform::Update()
{
	using namespace DirectX;

	ForEach([](Transform& _transform)
		{
			_transform.translateMatrix_ = XMMatrixTranslation(
				_transform.position_.x,
				_transform.position_.y,
				_transform.position_.z);
			_transform.rotateMatrix_ = XMMatrixRotationZ(_transform.rotation_.z)
				* XMMatrixRotationX(_transform.rotation_.x)
				* XMMatrixRotationY(_transform.rotation_.y);
			_transform.scaleMatrix_ = XMMatrixScaling(
				_transform.scale_.x,
				_transform.scale_.y,
				_transform.scale_.z);

			_transform.localMatrix_ = _transform.scaleMatrix_
				* _transform.rotateMatrix_
				* _transform.translateMatrix_;

			_transform.worldMatrix_ = XMMatrixIdentity();
			_transform.worldRotateMatrix_ = XMMatrixIdentity();
		});

	CPGameObject& cpGameObject{ System().Get<CPGameObject>() };
	CPGameObjectProperty& cpGameObjectProperty{ System().Get<CPGameObjectProperty>() };

	// êeèÓïÒÇéÊìæÇµÇƒÇ¢Ç≠
	std::map<EntityId, EntityId> parentMap{};
	std::map<EntityId, bool> check{};

	ForEach([&cpGameObject, &cpGameObjectProperty, &parentMap, &check, this](Transform& _transform, const size_t _index)
		{
			EntityId currentId{ cpGameObject.GetEntityId(_index) };
			GameObjectProperty* pCurrentProperty{ cpGameObjectProperty.Get(currentId) };
			
			wassert(!check.count(currentId) && "ä˘Ç…ìØÇ∂EntityIdÇ™Ç†ÇÈ");
			wassert(!parentMap.count(currentId) && "ä˘Ç…ìØÇ∂EntityIdÇ™Ç†ÇÈ");
			
			parentMap.insert({ currentId, pCurrentProperty->GetParent() });
			check.insert({ currentId, false });
		});

	std::stack<EntityId> calculateStack{};
	for (auto itr = parentMap.begin(); itr != parentMap.end(); itr++)
	{
		const auto [self, parent]{ *itr };

		if (check[self])
		{
			continue;
		}
		calculateStack.push(self);
		while (parentMap[calculateStack.top()] != INVALID_ENTITY)
		{
			calculateStack.push(parentMap[calculateStack.top()]);
		}

		while (!calculateStack.empty())
		{
			if (parentMap[calculateStack.top()] == INVALID_ENTITY)
			{
				at(calculateStack.top()).worldMatrix_ = at(calculateStack.top()).localMatrix_;
				at(calculateStack.top()).worldRotateMatrix_ = at(calculateStack.top()).rotateMatrix_;
			}
			else
			{
				at(calculateStack.top()).worldMatrix_ *= at(calculateStack.top()).localMatrix_ * at(parentMap[calculateStack.top()]).worldMatrix_;
				at(calculateStack.top()).worldRotateMatrix_ = at(calculateStack.top()).rotateMatrix_ * at(parentMap[calculateStack.top()]).worldRotateMatrix_;
			}
			check[calculateStack.top()] = true;
			calculateStack.pop();
		}
	}
}
