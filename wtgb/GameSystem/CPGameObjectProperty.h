#pragma once
#include "ComponentPool.h"
#include "GameComponent/GameObjectProperty.h"

namespace wtgb
{
	class GameObjectProperty;

	class CPGameObjectProperty : public ComponentPool<GameObjectProperty>
	{
	public:
		CPGameObjectProperty();
		~CPGameObjectProperty();

		/// <summary>
		/// ‰Šú‰»ˆ—
		/// </summary>
		void Init() override;
		/// <summary>
		/// XVˆ—
		/// </summary>
		void Update() override;
	};
}
