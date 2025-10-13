#pragma once

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
	};
}
