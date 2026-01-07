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

		virtual void Init(ViewerCached _system) override {};
		virtual void Update(ViewerCached _system) override {};
		virtual void End() override{};
	};
}
