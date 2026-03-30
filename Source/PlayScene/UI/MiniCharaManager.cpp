#include "MiniCharaManager.h"
#include "MiniChara.h"
#include "../../SMF/SMFPlayer.h"


MiniCharaManager::MiniCharaManager(const EntityId _smfPlayer) :
	GameObject{ "Play/UI/MiniCharaManager.json" },
	currentLevel_{ CloudLevel::CLOUD_LEVEL_START },
	smfPlayer_{ _smfPlayer },
	imageSize_{},
	iamgeScale_{},
	orbMoveTime_{}
{
}

MiniCharaManager::~MiniCharaManager()
{}

void MiniCharaManager::Init()
{
	OnLoad(GetComponent<Parameter>().Load());
}

void MiniCharaManager::Update()
{}

void MiniCharaManager::Release()
{}

void MiniCharaManager::LevelUp(const CloudLevel _current)
{
	const Vector2Int SCREEN_SIZE{ System().Get<GameWindow>().GetMainWindowSize() };

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
				spawanType = MiniCharaType_Base3;
				break;
			case CLOUD_LEVEL_TUBA:
				spawanType = MiniCharaType_Tubar;
				break;
			case CLOUD_LEVEL_DRUM:
				spawanType = MiniCharaType_Monkitty;
				break;
			case CLOUD_LEVEL_GLOCKEN:
				spawanType = MiniCharaType_Glocken;
				break;
			case CLOUD_LEVEL_START:
			case CLOUD_LEVEL_MAX:
			default:
				break;
			}
			Vector2Int beginPosition
			{
				GetMiniCharaPositionX(static_cast<int>(miniCharars_.size())),
				SCREEN_SIZE.y - 1
			};
			// ミニキャラを登場させる
			miniCharars_.push_back(
				pGameScene->Instantiate<MiniChara>(
					GetEntityId(),
					MiniChara::Config
					{
						pSMFPlayer->GetQuarterSec(),
						pSMFPlayer->GetQuarterSec(),
						spawanType,
						beginPosition,
						orbMoveTime_,
					}));
			MiniChara* pMiniChara{ FindGameObject<MiniChara>(miniCharars_.back()) };
			Vector2Int upperPosition{ beginPosition };
			upperPosition.y -= imageSize_.y;
			// 登場して画面下から飛び出すようにする
			pMiniChara->MoveAt(upperPosition);
		}
	}
	else
	{
		MiniChara* pMiniChara{ FindGameObject<MiniChara>(miniCharars_[currentLevel_ - 1]) };
		wassert(pMiniChara && "音を鳴らすミニキャラ取得に失敗");
		if (pMiniChara)
		{
			pMiniChara->MoveAt(
				{
					GetMiniCharaPositionX(static_cast<int>(currentLevel_)),
					SCREEN_SIZE.y - 1 - imageSize_.y
				});
		}
	}
}

void MiniCharaManager::LevelDown(const CloudLevel _current)
{
	const Vector2Int SCREEN_SIZE{ System().Get<GameWindow>().GetMainWindowSize() };

	MiniChara* pMiniChara{ FindGameObject<MiniChara>(miniCharars_[currentLevel_ - 1]) };
	wassert(pMiniChara && "音を鳴らすミニキャラ取得に失敗");
	if (pMiniChara)
	{
		pMiniChara->MoveAt({ GetMiniCharaPositionX(static_cast<int>(currentLevel_)), SCREEN_SIZE.y - 1 });
	}
	
	currentLevel_ = _current;
}

void MiniCharaManager::Rap(const CloudLevel _level, const float _ratioX)
{
	size_t index{ static_cast<size_t>(_level) };
	if (index < 0 || static_cast<size_t>(maxLevel_) < index)
	{
		wassert(false && "未登場の演奏レベルで音が鳴りました");
		return;
	}

	// TODO: スタートミニキャラを飛ばすために -1しているだけ
	MiniChara* pMiniChara{ FindGameObject<MiniChara>(miniCharars_[index - 1]) };
	wassert(pMiniChara && "音を鳴らすミニキャラ取得に失敗");

	if (pMiniChara)
	{
		pMiniChara->Rap(_ratioX);
	}
}

int MiniCharaManager::GetMiniCharaPositionX(const int _index)
{
	return imageSize_.x * _index;
}

void MiniCharaManager::OnLoad(const json& _json)
{
	imageSize_ = SafeGet<Vector2Int>(_json, "imageSize");
	iamgeScale_ = SafeGet<float>(_json, "iamgeScale");
	orbMoveTime_ = SafeGet<float>(_json, "orbMoveTime");
}

bool MiniCharaManager::TryUpdateMaxLevel()
{
	if (currentLevel_ > maxLevel_)
	{
		maxLevel_ = currentLevel_;

		return true;  // 最高レベルを更新した
	}
	// 更新しなかった
	return false;
}
