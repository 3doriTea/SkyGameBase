#pragma once
#include "GameSystem/ComponentPool.h"

#define COMPONENT_POOL(COMPONENT_NAME)\
COMPONENT_NAME; class CP##COMPONENT_NAME : public wtgb::ComponentPool<COMPONENT_NAME>


