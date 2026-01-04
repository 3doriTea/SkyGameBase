#pragma once
#include "Helper/CommonGameComponent.h"
#include "../Systems/CPItemAnim.h"

enum struct ItemType : uint32_t
{
	PresentRedSphere,  // ê‘ä€ÉvÉåÉ[ÉìÉg
};

class COMPONENT(ItemAnim)
{
public:
	class SETTER(ItemAnim)
	{
		SETTER_HEAD(ItemAnim)

		SETTER_PARAM(ItemType, itemType)
	};

private:
	ItemType itemType_;
};
