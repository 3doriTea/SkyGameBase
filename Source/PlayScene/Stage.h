#pragma once
#include <wtgb.h>

class Stage : public GameObject
{
public:
	Stage();
	~Stage();

	void Init() override;
	void Update() override;


};
