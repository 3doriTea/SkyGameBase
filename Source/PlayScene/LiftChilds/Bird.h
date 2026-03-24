#pragma once
#include "LiftChild.h"

class Bird : public LiftChild
{
public:
	Bird() = default;
	~Bird() = default;

private:
	ModelHandle hModel_;
};
