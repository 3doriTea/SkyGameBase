#pragma once
#include "Helper/CommonGameComponentPool.h"
#include "Components/ItemAnim.h"


class COMPONENT_POOL(ItemAnim)
{
public:
	CPItemAnim();
	~CPItemAnim();

	const CallType GetCallType() override { return CallType::Frame; }

	wtgb::Result Init(const ViewerInit& _viewer) override;
	void Update(const ViewerUpdate& _system) override;
	void End() override;
};
