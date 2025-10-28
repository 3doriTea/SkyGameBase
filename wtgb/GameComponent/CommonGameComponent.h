#pragma once

#include "Core/Component.h"
#include "Core/ComponentSetter.h"

#define COMPONENT(COMPONENT_NAME)\
CP##COMPONENT_NAME;\
class COMPONENT_NAME : public Component<CP##COMPONENT_NAME>

#define SETTER(COMPONENT_NAME)\
Setter : public ComponentSetter<COMPONENT_NAME>

#define SETTER_HEAD(COMPONENT_NAME)\
public:\
	using ComponentSetter<COMPONENT_NAME>::ComponentSetter;\
	~Setter() {}

#define SETTER_PARAM(TYPE, UNIT_NAME)\
	Setter& UNIT_NAME(const TYPE& _##UNIT_NAME) { GetAccess()->UNIT_NAME##_ = _##UNIT_NAME; return *this; }
