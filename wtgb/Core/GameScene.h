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
		GameScene(Config&& _config);
		virtual ~GameScene();

		virtual void Start() {}
		virtual void Update() {}
		virtual void Draw() {}

	protected:
		template<GameObjectT T, typename ...Args>
		GameObject Instantiate(Args... _args);
	};
}
