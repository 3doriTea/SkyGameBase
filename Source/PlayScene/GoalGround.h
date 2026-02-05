#pragma once
#include <wtgb.h>


/// <summary>
/// ‹È‚ÌÄ¶‚ªI‚í‚é‚ÆŒ»‚ê‚éƒS[ƒ‹
/// </summary>
class GoalGround : public GameObject
{
public:
	GoalGround(const Vector3& _position);
	~GoalGround();

	void Init() override;
	void Update() override;
	void Release() override;

private:

};

