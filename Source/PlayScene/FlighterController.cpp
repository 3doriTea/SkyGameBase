#include "FlighterController.h"
#include "LiftStructure.h"
//#include "Player.h"


FlighterController::FlighterController(
	const EntityId _liftStructure,
	const EntityId _player) :
	GameObject{ "Play/FlighterController.json" },
	liftStructure_{ _liftStructure },
	player_{ _player }
{
}

FlighterController::~FlighterController()
{
}

void FlighterController::Init()
{

}

void FlighterController::Update()
{
	LiftStructure* pLiftStructure{ FindGameObject<LiftStructure>(liftStructure_) };
	wassert(pLiftStructure && "リフト本体が見つからなかった");

	GameObject* pPlayerObj{ FindGameObject(player_) };

	if (pLiftStructure)
	{
		EntityId foundChair
		{
			pLiftStructure->FindChair(
				pPlayerObj->Transform().GetPosition(),
				LiftChairDir::ToDown)
		};

		if (foundChair != INVALID_ENTITY)
		{
			GameObject* pChairObj{ FindGameObject(foundChair) };
			if (pChairObj)
			{
				Transform().SetPosition(pChairObj->Transform().GetPosition());
			}
		}
	}
}

void FlighterController::Release()
{
}
