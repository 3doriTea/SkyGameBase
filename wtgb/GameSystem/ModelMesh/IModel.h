#pragma once
#include "pch/pch.h"

namespace wtgb
{
	class IModel
	{
	public:
		IModel();
		virtual ~IModel();

		bool TryLoad();


	};
}
