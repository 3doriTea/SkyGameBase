#pragma once
#include <wtgb.h>

class CharaEggRing : public GameObject
{
public:
	CharaEggRing(const EntityId _charaEgg, const Vector3& _position, const Vector3& _angles);
	~CharaEggRing();

	void Init() override;
	void Update() override;
};

class CharaEgg : public GameObject
{
public:
	CharaEgg(const Vector3& _position, const EntityId _stageObjManager, const EntityId _player);
	~CharaEgg();

	void Init() override;
	void Update() override;

private:
	EntityId stageObjManager_;
	EntityId player_;

	std::vector<EntityId> rings_;
};
