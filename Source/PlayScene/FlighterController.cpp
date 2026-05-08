#include "FlighterController.h"
#include "LiftStructure.h"
#include <wtgb/GameSystem/Model.h>
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
	OnLoadParam(GetComponent<Parameter>().Load());

	GetComponent<ModelMesh>().SetModel(hModel_);
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

void FlighterController::OnLoadParam(const json& _json)
{
	size_t modelsCount{ _json["modelsFileName"].size() };

	/*
	"ModelMesh": {
		"fileName": "Models/Sphere/Sphere.fbx",
		"modelMeshType": 5
	},
	*/

	std::string modelFileName{};
	_json["modelsFileName"][modelsCount].value(modelFileName, "Models/Flighter/Bird.fbx");

	hModel_ = System().Get<Model>().Load(modelFileName);

	GetComponent<ModelMesh>().SetModel(hModel_);
}
