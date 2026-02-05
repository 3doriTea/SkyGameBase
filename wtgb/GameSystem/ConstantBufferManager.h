#pragma once
#include "Core/IGameSystem.h"


namespace wtgb
{
	class ConstantBufferManager : public IGameSystem
	{
	public:
		ConstantBufferManager();
		~ConstantBufferManager();

		const CallType GetCallType() override { return CallType::Frame; }

		Result Init(const ViewerInit& _viewer) override;
		void Update(const ViewerUpdate& _viewer) override;
		void End() override;
	};
}
