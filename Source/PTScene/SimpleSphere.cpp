#include "SimpleSphere.h"

SimpleSphere::SimpleSphere(const Vector3 _position) :
	GameObject{ "PT/SimpleSphere.json" }
{
	Transform().SetPosition(_position);
}

SimpleSphere::~SimpleSphere()
{
}

void SimpleSphere::Init()
{
}

void SimpleSphere::Update()
{
}

void SimpleSphere::Release()
{
}
