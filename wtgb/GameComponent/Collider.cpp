#include "pch/pch.h"
#include "Collider.h"
#include "WTGBAssert.h"
#include "GameSystem/CPRigidBody.h"
#include "GameSystem/CPRigidBody/PhysicsUtil.h"

wtgb::Collider::Collider() :
	colliderType_{}
{
	sphere =
	{
		.radius = 1.0f,
		.center = Vector3::Zero(),
	};
	section = {};
}

wtgb::Collider::Collider(const Collider& _other) :
	colliderType_{ _other.colliderType_ }
{
	sphere =
	{
		.radius = 1.0f,
		.center = Vector3::Zero(),
	};
	section = {};

	switch (_other.colliderType_)
	{
	case Type::Section:
		section = _other.section;
		break;
	case Type::Sphere:
		sphere = _other.sphere;
		break;
	default:
		wassert(false && "–¢ŽÀ‘•‚Ì“–‚½‚è”»’èƒ^ƒCƒv");
		break;
	}
}
