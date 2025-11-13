#pragma once
#include "GameSystemViewer.h"

namespace wtgb
{
	class IComponent
	{
	public:
		IComponent() {}
		virtual ~IComponent() {}

		virtual void Init(ViewerCached system_) = 0;
		virtual void Update(ViewerCached system_) = 0;
		virtual void End() = 0;
	};
}
