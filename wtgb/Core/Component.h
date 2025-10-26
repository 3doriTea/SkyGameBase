#pragma once
#include "IComponent.h"

namespace wtgb
{
	template<typename ComponentPoolT>
	class Component : public IComponent
	{
	public:
		using PoolT = ComponentPoolT;

	public:
		Component() {}
		virtual ~Component() {}

		virtual void Update() override {}
	};
}
