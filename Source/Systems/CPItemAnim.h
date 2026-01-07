#pragma once
#include "Helper/CommonGameComponentPool.h"
#include "Components/ItemAnim.h"


class COMPONENT_POOL(ItemAnim)
{
public:
	CPItemAnim();
	~CPItemAnim();

	const CallType GetCallType() override { return CallType::Frame; }

	void Init() override;
	void Update() override;
};
