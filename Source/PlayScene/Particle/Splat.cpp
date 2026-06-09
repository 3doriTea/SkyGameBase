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
	//if ()
}

void Splat::Release()
{
}
