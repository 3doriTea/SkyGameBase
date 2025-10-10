#pragma once

namespace wtgb
{
	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject();

		void Init();
		void Update();
		void Draw() const;
		void Release();
	};
}
