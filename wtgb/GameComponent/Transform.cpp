#include "pch\pch.h"
#include "Transform.h"

wtgb::Matrix4x4 wtgb::Transform::GetWorldMatrix() const
{
	//assert(false && "TODO:親子関係込みのワールド行列");
	return localMatrix_;
}
