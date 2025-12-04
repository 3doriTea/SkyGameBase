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

	ForEach([this](Transform& _transform)
		{
			CalculateLocalTransform(&_transform);

			_transform.worldMatrix_ = XMMatrixIdentity();
			_transform.worldRotateMatrix_ = XMMatrixIdentity();
		});

	CPGameObject& cpGameObject{ System().Get<CPGameObject>() };
	CPGameObjectProperty& cpGameObjectProperty{ System().Get<CPGameObjectProperty>() };

	// 親情報を取得していく
	std::map<EntityId, EntityId> parentMap{};
	std::map<EntityId, bool> check{};

	ForEach([&cpGameObject, &cpGameObjectProperty, &parentMap, &check, this](Transform& _transform, const size_t _index)
		{
			EntityId currentId{ cpGameObject.GetEntityId(_index) };
			GameObjectProperty* pCurrentProperty{ cpGameObjectProperty.Get(currentId) };
			
			wassert(!check.count(currentId) && "既に同じEntityIdがある");
			wassert(!parentMap.count(currentId) && "既に同じEntityIdがある");
			
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
				// 親がいないなら
				CalculateTransformRoot(&at(calculateStack.top()));
			}
			else
			{
				// 親がいるなら親との計算をする
				at(calculateStack.top()).worldMatrix_ *= at(calculateStack.top()).localMatrix_ * at(parentMap[calculateStack.top()]).worldMatrix_;
				at(calculateStack.top()).worldRotateMatrix_ = at(calculateStack.top()).rotateMatrix_ * at(parentMap[calculateStack.top()]).worldRotateMatrix_;
			}
			check[calculateStack.top()] = true;
			calculateStack.pop();
		}
	}
}

void wtgb::CPTransform::CalculateLocalTransform(Transform* _pTransform)
{
	using namespace DirectX;

	_pTransform->translateMatrix_ = XMMatrixTranslation(
		_pTransform->position_.x,
		_pTransform->position_.y,
		_pTransform->position_.z);
	
	_pTransform->rotateMatrix_ = XMMatrixRotationZ(_pTransform->rotation_.z)
		* XMMatrixRotationX(_pTransform->rotation_.x)
		* XMMatrixRotationY(_pTransform->rotation_.y);
	
	_pTransform->scaleMatrix_ = XMMatrixScaling(
		_pTransform->scale_.x,
		_pTransform->scale_.y,
		_pTransform->scale_.z);

	_pTransform->localMatrix_ = _pTransform->scaleMatrix_
		* _pTransform->rotateMatrix_
		* _pTransform->translateMatrix_;
}

void wtgb::CPTransform::CalculateTransformRoot(Transform* _pRoot)
{
	// ルートは自身のローカル行列がワールド行列として使える
	_pRoot->worldMatrix_ = _pRoot->localMatrix_;
	_pRoot->worldRotateMatrix_ = _pRoot->rotateMatrix_;
}
