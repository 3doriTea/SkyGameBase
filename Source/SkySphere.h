#pragma once
#include <wtgb.h>

class SkySphere : public GameObject
{
public:
	SkySphere();
	~SkySphere();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	//EntityId mainCamera_;  // カメラ

};