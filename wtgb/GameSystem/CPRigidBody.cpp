#include "pch\pch.h"
#include "CPRigidBody.h"

wtgb::CPRigidBody::CPRigidBody()
{
}

wtgb::CPRigidBody::~CPRigidBody()
{
}

void wtgb::CPRigidBody::Init()
{
}

void wtgb::CPRigidBody::Update()
{
	ForEach([](RigidBody& _rb)
		{
			//_rb.velocity_
		});
}
