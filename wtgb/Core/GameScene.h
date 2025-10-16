#pragma once
#include "GameObject.h"

namespace wtgb
{
	/// <summary>
	/// ÉQÅ[ÉÄÉVÅ[Éì
	/// </summary>
	class GameScene
	{
	public:
		struct Config
		{
			
		};

	public:
		GameScene();
		virtual ~GameScene();

		virtual void StartRegister() {}
		virtual void Update() {}
		virtual void Draw() {}

	protected:
		template<GameObjectT T, typename ...Args>
		GameObject Instantiate(Args... _args);
	};
}
