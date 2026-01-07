#include "pch\pch.h"
#include "Transform.h"
#include "GameSystem/CPTransform.h"

wtgb::Transform::Transform() :
	position_{ Vector3::Zero() },
	rotation_{ Vector3::Zero() },
	scale_{ Vector3::One() }
{
}

void wtgb::Transform::SetPositionWorld(const Vector3& _worldPosition)
{
	using DirectX::XMVector3TransformCoord;
	using DirectX::XMMatrixInverse;

	// ローカル座標に変換する行列を作る
	Matrix4x4 toLocalMatrix{ XMMatrixInverse(nullptr, worldMatrix_ * XMMatrixInverse(nullptr, localMatrix_)) };

	// ローカル座標としてセットする
	position_ = XMVector3TransformCoord(_worldPosition, toLocalMatrix);
}

wtgb::Vector3 wtgb::Transform::GetPositionWorld() const
{
	using DirectX::XMVector3TransformCoord;

	// ローカル座標をワールド座標に変換する
	return XMVector3TransformCoord(position_, worldMatrix_ * XMMatrixInverse(nullptr, localMatrix_));
}

void wtgb::Transform::SetRotationWorld(const Vector3& _worldRotation)
{
	using DirectX::XMVector3TransformCoord;
	using DirectX::XMMatrixInverse;

	// ローカルラジアンオイラー角に変換する行列を作る
	Matrix4x4 toLocalMatrix{ XMMatrixInverse(nullptr, worldRotateMatrix_ * XMMatrixInverse(nullptr, rotateMatrix_)) };

	// ローカルラジアンオイラー角としてセットする
	rotation_ = XMVector3TransformCoord(_worldRotation, toLocalMatrix);
}

wtgb::Vector3 wtgb::Transform::GetRotationWorld() const
{
	using DirectX::XMVector3TransformCoord;
	
	// ローカルラジアンオイラー角をワールドラジアンオイラー角に変換する
	return XMVector3TransformCoord(rotation_, worldRotateMatrix_ * XMMatrixInverse(nullptr, rotateMatrix_));
}
