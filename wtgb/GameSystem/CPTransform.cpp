#include "pch\pch.h"
#include "CPTransform.h"

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
		});
}
