#pragma once
#include <wtgb.h>

class CharaBall : public GameObject
{
public:
	CharaBall(const Vector3& _position, const Vector3& _velocity);
	~CharaBall();

	void Init() override;
	void Update() override;
	void Release() override;

private:
};

