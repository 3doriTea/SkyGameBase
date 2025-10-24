#pragma once

namespace wtgb
{
	class GameObject;

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
		template<typename T, typename ...Args>
		GameObject* Instantiate(Args... _args) { return nullptr; }
	};
}
