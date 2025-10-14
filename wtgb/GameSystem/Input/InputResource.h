#pragma once
#include "pch/pch.h"
#include "../IResource.h"

namespace wtgb
{
	class InputResource : public IResource
	{
	public:
		InputResource();
		~InputResource();

	private:
		void Init() override;
		void Release() override;

		bool TryInitDirectInput8();

	private:
		LPDIRECTINPUT8 pDirectInput_;
		LPDIRECTINPUTDEVICE8 pKeyDevice_;
		LPDIRECTINPUTDEVICE8 pMouseDevice_;
	};
}
