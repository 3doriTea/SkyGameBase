#include "pch/pch.h"
#include "RigidBody.h"

wtgb::RigidBody::RigidBody() :
	velocity_{ Vector3::Zero() },
	drag_{ 1.0f },
	angularVelocity_{ Vector3::Zero() },
	angularDrag_{ 1.0f },
	useSphereCollider_{ false },
	useGravity_{ false }
{

}
