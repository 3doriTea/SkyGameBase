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
		});

	CPGameObject& cpGameObject{ System().Get<CPGameObject>() };
	CPGameObjectProperty& cpGameObjectProperty{ System().Get<CPGameObjectProperty>() };

	ForEach([&cpGameObject, &cpGameObjectProperty, this](Transform& _transform, const size_t _index)
		{
			EntityId entityId{ cpGameObject.GetEntityId(_index) };
			GameObjectProperty* pGameObjectProperty{ cpGameObjectProperty.Get(entityId) };
			wassert(pGameObjectProperty && "ゲームプロパティのコンポーネントの取得に失敗");

			std::stack<GameObjectProperty*> st{};
			st.push(pGameObjectProperty);
			while (true)
			{
				EntityId entityId{ st.top()->GetParent()};
				if (entityId == INVALID_ENTITY)
				{
					break;
				}
				GameObjectProperty* pGameObjectProperty{ cpGameObjectProperty.Get(entityId) };
				st.push(pGameObjectProperty);
			}


			Matrix4x4 matrix{};

			while (!st.empty())
			{
				if (st.size() == 2)
				{
					LOGFLN("size={}", st.size());
				}
				matrix *= at(st.top()->GetEntityId()).localMatrix_;
				_transform.worldRotateMatrix_ *= at(st.top()->GetEntityId()).rotateMatrix_;
				st.pop();
			}

			
		});
}
