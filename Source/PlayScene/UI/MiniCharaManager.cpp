#include "MiniCharaManager.h"
#include "MiniChara.h"
#include "../../SMF/SMFPlayer.h"


MiniCharaManager::MiniCharaManager(const EntityId _smfPlayer) :
	GameObject{ "Simple.json" },
	currentLevel_{ CloudLevel::CLOUD_LEVEL_START },
	smfPlayer_{ _smfPlayer }
{
}

MiniCharaManager::~MiniCharaManager()
{}

void MiniCharaManager::Init()
{
	//OnLoad(GetComponent<Parameter>().Load());
}

void MiniCharaManager::Update()
{}

void MiniCharaManager::Release()
{}

void MiniCharaManager::LevelUp(const CloudLevel _current)
{
	currentLevel_ = _current;
	if (TryUpdateMaxLevel())
	{
		GameScene* pGameScene{ GetScene() };
		wassert(pGameScene && "ゲームシーンの取得に失敗");
		SMFPlayer* pSMFPlayer{ FindGameObject<SMFPlayer>(smfPlayer_) };
		wassert(pSMFPlayer && "smfPlayerの取得に失敗");

		if (pGameScene && pSMFPlayer)
		{
			MiniCharaType spawanType{};
			switch (currentLevel_)
			{
			case CLOUD_LEVEL_BASE:
				spawanType = MiniCharaType::Base3;
				break;
			case CLOUD_LEVEL_TUBA:
				spawanType = MiniCharaType::Tubar;
				break;
			case CLOUD_LEVEL_DRUM:
				spawanType = MiniCharaType::Monkitty;
				break;
			case CLOUD_LEVEL_GLOCKEN:
				spawanType = MiniCharaType::Glocken;
				break;
			case CLOUD_LEVEL_START:
			case CLOUD_LEVEL_MAX:
			default:
				break;
			}
			miniCharars_.push_back(
				pGameScene->Instantiate<MiniChara>(
					GetEntityId(),
					MiniChara::Config
					{
						pSMFPlayer->GetQuarterSec(),
						pSMFPlayer->GetQuarterSec(),
						spawanType
					}));
		}
	}
}

void MiniCharaManager::LevelDown(const CloudLevel _current)
{
	currentLevel_ = _current;
}

void MiniCharaManager::OnLoad(const json& _json)
{
	
}

bool MiniCharaManager::TryUpdateMaxLevel()
{
	if (currentLevel_ > maxLevel_)
	{
		return true;  // 最高レベルを更新した
	}
	// 更新しなかった
	return false;
}
