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
	for (auto itr = this->begin(); itr != this->end(); itr++)
	{
		(*itr).translateMatrix_ = XMMatrixTranslation((*itr).position_.x, (*itr).position_.y, (*itr).position_.z);
		(*itr).rotateMatrix_ = XMMatrixRotationZ((*itr).rotation_.z)
			* XMMatrixRotationX((*itr).rotation_.x)
			* XMMatrixRotationY((*itr).rotation_.y);
		(*itr).scaleMatrix_ = XMMatrixScaling((*itr).scale_.x, (*itr).scale_.y, (*itr).scale_.z);

		(*itr).localMatrix_ = (*itr).scaleMatrix_ * (*itr).rotateMatrix_ * (*itr).translateMatrix_;
	}
}
