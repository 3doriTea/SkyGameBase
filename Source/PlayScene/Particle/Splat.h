#pragma once
#include <wtgb.h>

/// <summary>
/// 飛び跳ねる泥
/// </summary>
class Splat : public GameObject
{
public:
	Splat();
	~Splat();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	
};
