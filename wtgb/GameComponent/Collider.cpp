#include "pch/pch.h"
#include "Collider.h"
#include "WTGBAssert.h"

wtgb::Collider::Collider() :
	section{},
	colliderType_{}
{
}

wtgb::Collider::Collider(const Collider& _other) :
	section{},
	colliderType_{ _other.colliderType_ }
{
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
