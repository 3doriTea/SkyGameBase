#include "pch\pch.h"
#include "Transform.h"

wtgb::Transform::Transform() :
	position_{ Vector3::Zero() },
	rotation_{ Vector3::Zero() },
	scale_{ Vector3::One() }
{
}
