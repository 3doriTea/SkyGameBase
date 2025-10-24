#pragma once
#include <wtgb/wtgb.h>

class FirstSceneRegister : public IGameSystem
{
public:
	FirstSceneRegister() {}
	~FirstSceneRegister() {}

	const CallType GetCallType() override { return CallType::DoNotUpdate; }

	wtgb::Result Init(const ViewerInit& _viewer) override;

	void Update(const ViewerUpdate& _system) override {}

	void End() override {}
};
