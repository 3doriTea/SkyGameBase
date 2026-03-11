#include "pch\pch.h"
#include "DropCloud.h"
#include "Player.h"
#include "StageLine.h"
#include "SMF/SMFPlayer.h"
#include "PlayScene.h"
#include "PresentSphere.h"
#include "State/PlayState.h"
#include "GoalGround.h"
#include "TitleScene/TitleScene.h"
#include "ResultScene/ResultScene.h"
#include "ISpeedController.h"
#include "SMF/ToneHz.h"
#include "UI/MiniChara.h"


DropCloud::DropCloud(
	const EntityId _smfPlayer,
	const EntityId _gamePlayer,
	const EntityId _stageLine,
	const EntityId _playState,
	const EntityId _speedController) :
	GameObject{ "DropCloud.json" },
	smfPlayer_{ _smfPlayer },
	player_{ _gamePlayer },
	stageLine_{ _stageLine },
	playState_{ _playState },
	offsetHeight_{},
	dropDistanceZ_{},
	speedController_{ _speedController },
	level_{ CloudLevel::CLOUD_LEVEL_START },
	perfectTimer_{},
	prevBar_{}
{
}

DropCloud::~DropCloud()
{
}

void DropCloud::OnLoadParam(const json& _json)
{
	playSMFPath_ = SafeGet<std::string>(_json, "playSMFPath");
	offsetHeight_ = SafeGet<float>(_json, "offsetHeight");
	dropDistanceZ_ = SafeGet<float>(_json, "dropDistanceZ");
	destroyDistanceZ_ = SafeGet<float>(_json, "destroyDistanceZ");
	toResultSceneTime_ = SafeGet<float>(_json, "toResultSceneTime");
	playNoteNumberOffset_ = SafeGet<int>(_json, "playNoteNumberOffset");
	playRatioMaxVelocity_ = SafeGet<float>(_json, "playRatioMaxVelocity");
	playToneAudioFilePath_ = SafeGet<std::string>(_json, "playToneAudioFilePath");
	toneAudioFilePathBase_ = SafeGet<std::string>(_json, "toneAudioFilePathBase");
	toneAudioFilePathTuba_ = SafeGet<std::string>(_json, "toneAudioFilePathTuba");
	toneAudioFilePathDrum_ = SafeGet<std::string>(_json, "toneAudioFilePathDrum");
	toneAudioFilePathGlocken_ = SafeGet<std::string>(_json, "toneAudioFilePathGlocken");
}

void DropCloud::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());

	SMFPlayer* pSMFPlayer{ dynamic_cast<SMFPlayer*>(FindGameObject(smfPlayer_)) };
	if (pSMFPlayer)
	{
		Audio& audio{ System().Get<Audio>() };
		StageLine* pStageLine{ dynamic_cast<StageLine*>(FindGameObject(stageLine_)) };
		wassert(pStageLine && "ステージラインがシーンに存在しないよ！");

		hAudioBase_ = audio.Load(toneAudioFilePathBase_);
		hAudioCat_ = audio.Load(playToneAudioFilePath_);
		hAudioTuba_ = audio.Load(toneAudioFilePathTuba_);
		hAudioDrum_ = audio.Load(toneAudioFilePathDrum_);
		hAudioGlocken_ = audio.Load(toneAudioFilePathGlocken_);
		// ノーツ再生時の音源読み込み && セット
		/*pSMFPlayer->SetToneAudioHandle(
			);*/

		// ノーツの処理を登録
		pSMFPlayer->OnNote([this, pSMFPlayer, pStageLine](Note _note)
			{
				PlayScene* pPlayScene{ GetScene<PlayScene>() };
				if (pPlayScene == nullptr)
				{
					return;  // プレイシーンが取得できなければ何もしない
				}

				DroppedPresent droppedPresent
				{
					.entityId = pPlayScene->Instantiate<PresentSphere>(
						player_,
						Transform().GetPosition(),
						Vector3{ Transform().GetPosition().x, pStageLine->GetPosY(Transform().GetPosition()), Transform().GetPosition().z }),
					.note = _note,
					.hTone = INVALID_HANDLE,
					.toneOffset = 0,
				};

				switch (_note.channel)
				{
				case 0x03:
					droppedPresent.hTone = hAudioCat_;
					droppedPresent.toneOffset = SMF::C4_60_INDEX;
					break;
				case 0x01:
					if (level_ < CLOUD_LEVEL_BASE)
					{
						return;
					}
					droppedPresent.hTone = hAudioBase_;
					droppedPresent.toneOffset = 12 * 7;
					break;
				case 0x02:
					if (level_ < CLOUD_LEVEL_TUBA)
					{
						return;
					}
					droppedPresent.hTone = hAudioTuba_;
					droppedPresent.toneOffset = 12 * 7;
					break;
				case 0x09:
					if (level_ < CLOUD_LEVEL_DRUM)
					{
						return;
					}
					droppedPresent.hTone = hAudioDrum_;
					droppedPresent.toneOffset = 12 * 7;
					break;
				case 0x06:
					if (level_ < CLOUD_LEVEL_GLOCKEN)
					{
						return;
					}
					droppedPresent.note.playTime = 6.0f;
					droppedPresent.hTone = hAudioGlocken_;
					droppedPresent.toneOffset = SMF::C4_60_INDEX + 12 * 0;
					break;
				default:
					return;
				}
				droppedPresents_.push_back(droppedPresent);
			});

		PlayState* playState{ dynamic_cast<PlayState*>(FindGameObject(playState_)) };
		if (playState)
		{
			playState->OnChanged([pSMFPlayer](PlayState::Type _nextType) -> bool
				{
					if (_nextType == PlayState::Type::Falling)
					{
						// 次の状態が下山なら再生開始
						pSMFPlayer->Play();
						return true;
					}
					else
					{
						return false;
					}
				});
		}
	}
}

void DropCloud::Update()
{
	PlayState* playState{ FindGameObject<PlayState>(playState_) };
	if (playState && playState->GetState() != PlayState::Type::Falling)
	{
		return;  // 下山中以外は無視
	}

	const float dt{ System().Get<GameTime>().GetDeltaTime() };

	SMFPlayer* pSMFPlayer{ FindGameObject<SMFPlayer>(smfPlayer_) };
	wassert(pSMFPlayer && u8"SMFPlayerが見つからなかった");
	Player* pPlayer{ FindGameObject<Player>(player_) };
	wassert(pPlayer && u8"プレイヤーが見つからなかった");
	StageLine* pStageLine{ FindGameObject<StageLine>(stageLine_) };
	wassert(pStageLine && u8"ステージラインが見つからなかった");
	ISpeedController* pSpeedController{ FindGameObject<ISpeedController>(speedController_) };
	wassert(pSpeedController && u8"スピードコントローラが見つからなかった");


#pragma region 再生が終了したら1回だけゴール処理
	if (pSMFPlayer
		&& isFinished_ == false
		&& pSMFPlayer->IsFinished())
	{
		isFinished_ = true;
		System().Get<Alarm>().Add([this]
			{
				// 時間が経ったら結果シーンに遷移する
				System()
					.Get<SceneManager>()
					.Move<ResultScene>();
			},
			toResultSceneTime_);
	}
#pragma endregion

#pragma region プレイヤが進むたびに音符を進める処理
	RigidBody& playerRigidBody{ pPlayer->GetComponent<RigidBody>() };

	Vector3 velocity{ playerRigidBody.GetVelocity()};

	if (pSpeedController)
	{
		float playRate{};

		SpeedType speedType{ pSpeedController->GetSpeedType() };
		switch (speedType)
		{
		case SpeedType::Stop:
			// 止まっているなら完全に止める
			playRate = 0.0f;
			break;
		case SpeedType::TooSlow:
			// 十分ではないがある程度進んでいるならそのスピードに合わせる
			playRate = velocity.z / playRatioMaxVelocity_;
			perfectTimer_ -= dt;
			break;
		case SpeedType::Good:
			// 十分スピードがあるなら通常再生
			playRate = 1.0f;
			perfectTimer_ += dt;
			break;
		case SpeedType::Excissive:
			// 速すぎるなら止める
			perfectTimer_ -= dt;
			playRate = 0.0f;
			break;
		default:
			break;
		}
		pSMFPlayer->SetPlayRate(playRate);
	}
#pragma endregion

#pragma region レベルのアップダウン処理
	if (pSMFPlayer)
	{
		// 1小節の秒数
		const float BAR_TIME_SEC{ pSMFPlayer->GetQuarterSec() * 4.0f };

		int currBar{ static_cast<int>(pSMFPlayer->GetPlayTime() / BAR_TIME_SEC) };

		// 1小節の区切り目
		if (currBar != prevBar_)
		{
			if (perfectTimer_ >= BAR_TIME_SEC)
			{
				perfectTimer_ = 0.0f;

				level_ = static_cast<CloudLevel>(level_ + 1);  // レベルアップ
				if (level_ >= CLOUD_LEVEL_MAX)
				{
					level_ = static_cast<CloudLevel>(CLOUD_LEVEL_MAX - 1);
				}
				
				SpawanMiniChara();
			}
			else if (perfectTimer_ < 0.0f)
			{
				perfectTimer_ = 0;

				level_ = static_cast<CloudLevel>(level_ - 1);  // レベルダウン
				if (level_ < 0)
				{
					level_ = static_cast<CloudLevel>(0);
				}
			}
		}

		prevBar_ = currBar;
	}
#pragma endregion

	Vector3 position{ pPlayer->Transform().GetPosition() };
	position.z += dropDistanceZ_;
	position.y = pStageLine->GetPosY(position) + offsetHeight_;
	Transform().SetPosition(position);

	for (auto itr = droppedPresents_.begin(); itr != droppedPresents_.end();)
	{
		GameObject* pPresentObj{ FindGameObject(itr->entityId) };
		PresentSphere* pPresent{ dynamic_cast<PresentSphere*>(FindGameObject(itr->entityId)) };

		if ((position.z - pPresent->Transform().GetPosition().z) > destroyDistanceZ_)
		{
			pPresent->DestroyMe();
			itr = droppedPresents_.erase(itr);
			continue;
		}

		if (pPresent->IsHit())
		{
			pPresent->DestroyMe();
			itr = droppedPresents_.erase(itr);
			continue;
		}
		if (pPresent->CheckOnBounded())
		{
			itr->note.noteNumber -= playNoteNumberOffset_;
			pSMFPlayer->PlayTone(itr->note, itr->hTone, itr->toneOffset);
		}

		itr++;
	}
}

void DropCloud::Release()
{
}

void DropCloud::SpawanMiniChara()
{
	if (GameScene* pScene{ GetScene() }; pScene)
	{
		MiniCharaType spawanType{};
		switch (level_)
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

		pScene->Instantiate<MiniChara>(
			GetEntityId(),
			smfPlayer_,
			spawanType);
	}
}
