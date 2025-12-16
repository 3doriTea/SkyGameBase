#pragma once
#include "Core/IGameSystem.h"

namespace wtgb
{
	class Scriptable : public IGameSystem
	{
	public:
		Scriptable();
		~Scriptable();

		/// <summary>
		/// 更新のタイミング
		/// </summary>
		/// <returns>更新のタイミング</returns>
		const CallType GetCallType() override { return CallType::Frame; }

		Result Init(const ViewerInit& _viewer) override;

		void Update(const ViewerUpdate& _system) override;

		void End() override;

	private:
		
	};
}
