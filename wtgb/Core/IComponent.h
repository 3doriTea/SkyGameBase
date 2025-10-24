#pragma once
#include "pch/pch.h"
#include "GameObjectBuilder.h"

namespace wtgb
{
	class IComponent
	{
	public:
		IComponent() {}
		virtual ~IComponent() {}

		virtual void Update() = 0;
	};
}
