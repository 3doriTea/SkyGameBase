#include "FlighterController.h"
#include "LiftStructure.h"
#include <wtgb/GameSystem/Model.h>
//#include "Player.h"
#include "Flighter/FlighterObject.h"


FlighterController::FlighterController(
	const EntityId _liftStructure,
	const EntityId _player) :
	GameObject{ "Play/FlighterController.json" },
	liftStructure_{ _liftStructure },
	player_{ _player },
	hModel_{ INVALID_HANDLE },
	findChairForwardOffset_{},
	flighterCount_{},
	flighterFlags_{},
	flighterEntities_{},
	vFormationDistance_{}
{
}

FlighterController::~FlighterController()
{
}

void FlighterController::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());

	GetComponent<ModelMesh>().SetModel(hModel_);

	GameObject* pPlayerObj{ FindGameObject(player_) };
	if (pPlayerObj == nullptr)
	{
		wassert(false && "プレイヤーオブジェクト取得に失敗");
		return;
	}

	flighterEntities_.resize(flighterCount_);
}

void FlighterController::Update()
{
	LiftStructure* pLiftStructure{ FindGameObject<LiftStructure>(liftStructure_) };
	wassert(pLiftStructure && "リフト本体が見つからなかった");
	GameObject* pPlayerObj{ FindGameObject(player_) };
	wassert(pPlayerObj && "プレイヤーオブジェクトが見つからなかった");

	if (pLiftStructure)
	{
		EntityId foundChair
		{
			pLiftStructure->FindChair(
				pPlayerObj->Transform().GetPosition() + Vector3::Forward() * findChairForwardOffset_,
				LiftChairDir::ToDown)
		};

		if (foundChair != INVALID_ENTITY)
		{
			// 空きを線形探索する
			uint32_t index{ 0 };
			while (index < flighterCount_)
			{
				if (flighterEntities_[index] == INVALID_ENTITY)
				{
					break;
				}
				index++;
			}

			// 見つかった！
			if (index < flighterCount_)
			{
				EntityId flighterObject
				{
					GetScene()->Instantiate<FlighterObject>(
						GetEntityId(),
						player_,
						foundChair,
						static_cast<uint8_t>(0),
						hModel_)
				};

				flighterEntities_[index] = flighterObject;

				FlighterObject* pflighterObj{ FindGameObject<FlighterObject>(flighterObject) };
				if (pflighterObj == nullptr)
				{
					wassert(false && "飛行オブジェクトの取得に失敗");
				}

				VFormationPosition vFormationPosition{ GetVFormationPosition(index) };

				pflighterObj->ReFollow(
					foundChair,
					vFormationPosition.x,
					0.0f,
					vFormationPosition.z);
			}

			GameObject* pChairObj{ FindGameObject(foundChair) };
			if (pChairObj)
			{
				Vector3 position{ pChairObj->Transform().GetPosition() };
				position.x = pPlayerObj->Transform().GetPosition().x;
				Transform().SetPosition(position);
			}
		}
	}
}

void FlighterController::Release()
{
}

void FlighterController::OnLoadParam(const json& _json)
{
	flighterCount_ = _json.value("flighterCount", 5);
	findChairForwardOffset_ = _json.value("findChairForwardOffset", 30.0f);
	vFormationDistance_ = _json.value("vFormationDistance", 30.0f);

	size_t modelsCount{ _json["modelsFileName"].size() };

	/*
	"ModelMesh": {
		"fileName": "Models/Sphere/Sphere.fbx",
		"modelMeshType": 5
	},
	*/

	std::string modelFileName{};
	_json["modelsFileName"][0].get_to(modelFileName);

	hModel_ = System().Get<Model>().Load(modelFileName);

	GetComponent<ModelMesh>().SetModel(hModel_);
}

FlighterController::VFormationPosition FlighterController::GetVFormationPosition(const uint32_t _index) const
{
	VFormationPosition position{};

	position.x = vFormationDistance_ * static_cast<float>(_index / 2);
	position.z = vFormationDistance_ * position.x * static_cast<float>(_index % 2 == 1 ? 1 : -1);

	LOGFLN("VFormationPosition[{}]: ({}, {})", _index, position.x, position.z);

	return position;
}
