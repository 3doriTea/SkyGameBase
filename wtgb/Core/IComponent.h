#pragma once
#include "pch/pch.h"
#include "GameObjectBuilder.h"

namespace wtgb
{
	template<typename SetterT>
	class IComponent
	{
	public:
		IComponent() {}
		virtual ~IComponent() {}

		virtual void Update() = 0;
	};
}
