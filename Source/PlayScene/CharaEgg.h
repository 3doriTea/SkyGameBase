#pragma once
#include <wtgb.h>

class CharaEggRing : public GameObject
{
public:
	CharaEggRing(const EntityId _charaEgg, const Vector3& _angles);
	~CharaEggRing();

	void Init() override;
	void Update() override;
	void Release() override;
};

class CharaEgg : public GameObject
{
public:
	CharaEgg(const Vector3& _position, const EntityId _stageObjManager, const EntityId _player);
	~CharaEgg();

	void OnLoadParam(const json& _json) override;

	void Init() override;
	void Update() override;
	void Release() override;

private:
	EntityId stageObjManager_;
	EntityId player_;

	std::vector<EntityId> rings_;       // ‰ñ‚è‚ğ‰ñ‚é‰~
	std::vector<Vector3> ringsAngles_;  // ‰ñ‚è‚ğ‰ñ‚é‰~‚ÌŠp“x
	float rotAngleSpeedPerSec_;         // ‰ñ‚è‚ğ‰ñ‚é‰~‚ÌƒXƒs[ƒh
};
