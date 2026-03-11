#pragma once
#include <wtgb.h>


/// <summary>
/// デバッガ
/// </summary>
class Debugger : public GameObject
{
public:
	Debugger();
	~Debugger();

	void Init() override;
	void Update() override;
	void Release() override;
};
