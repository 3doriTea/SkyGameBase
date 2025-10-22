#pragma once

namespace wtgb
{
	class IComponentPool
	{
	public:
		IComponentPool() {}
		virtual ~IComponentPool() {}

		virtual void Update() = 0;
	};
}