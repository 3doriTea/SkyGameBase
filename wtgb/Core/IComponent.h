#pragma once

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
