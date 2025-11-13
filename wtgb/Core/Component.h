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

		virtual void Init(ViewerCached system_) override {};
		virtual void Update(ViewerCached system_) override {};
		virtual void End() override{};
	};
}
