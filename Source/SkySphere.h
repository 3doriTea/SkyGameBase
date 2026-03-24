#pragma once
#include <wtgb.h>


/// <summary>
/// 一番背景の青空
/// </summary>
class SkySphere : public GameObject
{
public:
	SkySphere();
	~SkySphere();

	void Init() override;
	void Update() override;
	void Release() override;
};