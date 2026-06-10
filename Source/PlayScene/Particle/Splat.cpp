#include "Splat.h"

Splat::Splat(const Vector3 _position, const Vector3 _velocity) :
	GameObject{ "Play/Particle/Splat.json" }
{
	Transform().SetPosition(_position);
	GetComponent<RigidBody>().AddVelocity(_velocity);
}

Splat::~Splat()
{
}

void Splat::Init()
{
}

void Splat::Update()
{
	const float LESS_SIZE{ 0.3f };
	const float DESTROY_THRESHOLD{ 0.1f };

	if (GetComponent<RigidBody>().IsHit())
	{
		Vector3 scale = Transform().GetScale();
		scale = scale - Vector3::One() * LESS_SIZE;

		if (scale.x < DESTROY_THRESHOLD)
		{
			Transform().SetScale(Vector3::Zero());
			DestroyMe();
		}
		else
		{
			Transform().SetScale(scale);
		}
	}
}

void Splat::Release()
{
}
