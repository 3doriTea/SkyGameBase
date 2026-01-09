#include "SkySphere.h"

SkySphere::SkySphere() :
	GameObject{ "SkySphere.json" }
{
	EntityId mainCamera{ FindGameObject("CamCon")->GetEntityId() };
	Property().SetParent(mainCamera);  // í‚ÉƒJƒƒ‰‚É‚­‚Á‚Â‚­‚æ‚¤‚É‚·‚é
}

SkySphere::~SkySphere()
{
}

void SkySphere::Init()
{
}

void SkySphere::Update()
{
}

void SkySphere::Release()
{
}
