#pragma once
#include <wtgb.h>

/// <summary>
/// 飛び跳ねる泥
/// </summary>
class Splat : public GameObject
{
public:
	Splat(const Vector3 _position, const Vector3 _velocity);
	~Splat();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	
};
