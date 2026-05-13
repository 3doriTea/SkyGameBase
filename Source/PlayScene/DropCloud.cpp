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
#include "UI/MiniCharaManager.h"
#include "UI/PerfectTimer.h"
#include "Systems/ScoreManager.h"
#include "../FaderController.h"


DropCloud::DropCloud(
	const EntityId _smfPlayer,
	const EntityId _gamePlayer,
	const EntityId _stageLine,
	const EntityId _playState,
	const EntityId _speedController,
	const EntityId _miniCharaManager,
	const EntityId _faderController) :
	GameObject{ "DropCloud.json" },
	smfPlayer_{ _smfPlayer },
	player_{ _gamePlayer },
	stageLine_{ _stageLine },
	playState_{ _playState },
	miniCharaManager_{ _miniCharaManager },
	faderController_{ _faderController },
	offsetHeight_{},
	dropDistanceZ_{},
	speedController_{ _speedController },
	level_{ CloudLevel::CLOUD_LEVEL_START },
	perfectTimer_{},
	prevBar_{},
	destroyDistanceZ_{},
	hAudios_{},
	isFinished_{},
	playNoteNumberOffset_{},
	perfectTimerUI_{ INVALID_ENTITY },
	playRatioMaxVelocity_{},
	toResultSceneTime_{}
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
	// TOOD: ここもまとめる
	int miniCharaType{};
	for (auto& toneAudioFileJson : _json["toneAudioFiles"])
	{
		toneAudioFilesPath_.at(miniCharaType) = toneAudioFileJson.get<std::string>();
		miniCharaType++;
	}
}

void DropCloud::DropPresent(const Note _note)
{
	System().Get<ScoreManager>().Ref([](GameScore& _score)
		{
			_score.presentCount++;
		});

	PlayScene* pPlayScene{ GetScene<PlayScene>() };
	WorldConfig worldConfig{ pPlayScene->GetWorldConfig() };

	SMFPlayer* pSMFPlayer{ FindGameObject<SMFPlayer>(smfPlayer_) };
	wassert(pSMFPlayer && "SMFPlayerの取得に失敗");

	MiniCharaManager* pMiniCharaManager{ FindGameObject<MiniCharaManager>(miniCharaManager_) };
	wassert(pMiniCharaManager && "ミニキャラ統括するやつが見つからない");

	StageLine* pStageLine{ FindGameObject<StageLine>(stageLine_) };
	wassert(pStageLine && "ステージラインがシーンに存在しないよ！");

	if ((pPlayScene && pSMFPlayer && pMiniCharaManager && pStageLine) == false)
	{
		return;  // 参照できないものがあれば何もできない
	}

	// プレゼント
	DroppedPresent droppedPresent
	{
		.entityId = INVALID_ENTITY,
		.note = _note,
		.hTone = INVALID_HANDLE,
		.toneOffset = 0,
	};

	// 演奏レベルフィルタ
	CloudLevel level{};
	switch (_note.channel)
	{
	case 0x03:
		level = CLOUD_LEVEL_START;
		droppedPresent.hTone = hAudios_[MiniCharaType_T];
		droppedPresent.toneOffset = SMF::C4_60_INDEX;
		break;
	case 0x01:
		level = CLOUD_LEVEL_BASE;
		if (level_ < CLOUD_LEVEL_BASE)
		{
			return;
		}
		droppedPresent.hTone = hAudios_[MiniCharaType_Base3];
		droppedPresent.toneOffset = 12 * 7;
		break;
	case 0x02:
		level = CLOUD_LEVEL_TUBA;
		if (level_ < CLOUD_LEVEL_TUBA)
		{
			return;
		}
		droppedPresent.hTone = hAudios_[MiniCharaType_Tubar];
		droppedPresent.toneOffset = 12 * 7;
		break;
	case 0x09:
		level = CLOUD_LEVEL_DRUM;
		if (level_ < CLOUD_LEVEL_DRUM)
		{
			return;
		}
		droppedPresent.hTone = hAudios_[MiniCharaType_Monkitty];
		droppedPresent.toneOffset = 12 * 7;
		break;
	case 0x06:
		level = CLOUD_LEVEL_GLOCKEN;
		if (level_ < CLOUD_LEVEL_GLOCKEN)
		{
			return;
		}
		droppedPresent.note.playTime = 6.0f;
		droppedPresent.hTone = hAudios_[MiniCharaType_Glocken];
		droppedPresent.toneOffset = SMF::C4_60_INDEX + 12 * 0;
		break;
	default:
		return;
	}

	// プレゼントの出現座標
	Vector3 fromPosition{ Transform().GetPosition() };

	auto& [toneMin, toneMax] { pSMFPlayer->GetChannelToToneMinMax(_note.channel) };
	// プレゼントを投下する音階範囲内でのレート
	float toneRatio
	{
		static_cast<float>(_note.noteNumber - toneMin)
			/ (toneMax - toneMin)
	};

	fromPosition.x = Mathf::Lerp(
		worldConfig.safeZoneXMin,
		worldConfig.safeZoneXMax,
		toneRatio);

	// プレゼントの投下地点の座標
	Vector3 toPosition{ fromPosition.x, pStageLine->GetPosY(fromPosition), fromPosition.z };

	// プレゼント生成
	droppedPresent.entityId = pPlayScene->Instantiate<PresentSphere>(
		player_,
		fromPosition,
		toPosition);

	droppedPresents_.push_back(droppedPresent);

	if (level == CLOUD_LEVEL_START)
	{
		return;  // スタートレベルは音符出さない
	}

	pMiniCharaManager->Rap(level, toneRatio);
}

void DropCloud::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());

	GameScene* pGameScene{ GetScene() };
	wassert(pGameScene && "シーン取得に失敗");
	if (pGameScene)
	{
		perfectTimerUI_ = pGameScene->Instantiate<PerfectTimer>();
	}

	SMFPlayer* pSMFPlayer{ FindGameObject<SMFPlayer>(smfPlayer_) };
	if (pSMFPlayer)
	{
		Audio& audio{ System().Get<Audio>() };

		// ミニキャラの読み込み
		for (int miniCharaType{}; miniCharaType < MiniCharaType_Max; miniCharaType++)
		{
			hAudios_[miniCharaType] = audio.Load(toneAudioFilesPath_[miniCharaType]);
		}

		// ノーツの処理を登録
		pSMFPlayer->OnNote([this](Note _note)
			{
				// 再生時にプレゼントを投下！
				DropPresent(_note);
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

	const float DT{ System().Get<GameTime>().GetDeltaTime() };

	SMFPlayer* pSMFPlayer{ FindGameObject<SMFPlayer>(smfPlayer_) };
	wassert(pSMFPlayer && u8"SMFPlayerが見つからなかった");
	
	Player* pPlayer{ FindGameObject<Player>(player_) };
	wassert(pPlayer && u8"プレイヤーが見つからなかった");
	
	StageLine* pStageLine{ FindGameObject<StageLine>(stageLine_) };
	wassert(pStageLine && u8"ステージラインが見つからなかった");
	
	ISpeedController* pSpeedController{ FindGameObject<ISpeedController>(speedController_) };
	wassert(pSpeedController && u8"スピードコントローラが見つからなかった");
	
	MiniCharaManager* pMiniCharaManager{ FindGameObject<MiniCharaManager>(miniCharaManager_) };
	wassert(pMiniCharaManager && "ミニキャラ統括するやつが見つからない");


#ifdef _DEBUG
	// デバッグ用 すぐにリザルトシーンへ行く
	const Input::InputGetter& input{ System().Get<Input>().Getter() };
	if (input.IsKeyDown(KeyCode::Alpha0) && isFinished_ == false)
	{
		isFinished_ = true;
		System().Get<Alarm>().Add([this]
			{
				// 時間が経ったら結果シーンに遷移する
				System()
					.Get<SceneManager>()
					.Move<ResultScene>();
			},
			0.0f);
	}
#endif

#pragma region 再生が終了したら1回だけゴール処理
	if (pSMFPlayer
		&& isFinished_ == false
		&& pSMFPlayer->IsFinished())
	{
		isFinished_ = true;


		System().Get<Alarm>().Add([this]
			{
				if (System().Get<ScoreManager>().IsFailedGoal()
					== false)  // ゴール失敗していない！
				{
					FaderController* pFaderController{ FindGameObject<FaderController>(faderController_) };
					pFaderController->Hide([this]
						{
							// 時間が経ったら結果シーンに遷移する
							System()
								.Get<SceneManager>()
								.Move<ResultScene>();
						});
				}
			},
			toResultSceneTime_);
	}
#pragma endregion

#pragma region プレイヤーがゴール不可能時にゴール失敗処理
	if (!isFinished_)
	{
		const float STOPPER_POS_Z{ pStageLine->GetStopperStartPosZ() };
		Vector3 playerPosition{ pPlayer->Transform().GetPosition() };
		if (playerPosition.z >= STOPPER_POS_Z
			&& isFinished_ == false)
		{
			isFinished_ = true;
			// ストッパーに侵入してしまったなら、失敗
			System().Get<ScoreManager>().FailedGoal();
			System().Get<Alarm>().Add([this]
				{
					// 時間が経ったら結果シーンに遷移する
					System()
						.Get<SceneManager>()
						.Move<ResultScene>();
				},
				toResultSceneTime_);
		}
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
			if (level_ > 0)
			{
				perfectTimer_ = std::fmaxf(perfectTimer_ + DT, 0.0f);
			}

			System().Get<ScoreManager>().Ref([DT](GameScore& _score)
				{
					// ずれている時間を計測
					_score.timeDifference += DT;
				});
			break;
		case SpeedType::Good:
			// 十分スピードがあるなら通常再生
			playRate = 1.0f;
			if (level_ < CLOUD_LEVEL_MAX)
			{
				perfectTimer_ += DT;
			}
			break;
		case SpeedType::Excissive:
			// 速すぎるなら止める
			if (level_ > 0)
			{
				perfectTimer_ = std::fmaxf(perfectTimer_ + DT, 0.0f);
			}
			playRate = 0.0f;

			System().Get<ScoreManager>().Ref([DT](GameScore& _score)
				{
					// ずれている時間を計測
					_score.timeDifference += DT;
				});
			break;
		default:
			break;
		}
		pSMFPlayer->SetPlayRate(playRate);
	}
#pragma endregion

#pragma region レベルのアップダウン処理
	// 1小節の秒数
	const float BAR_TIME_SEC{ pSMFPlayer->GetQuarterSec() * 4.0f };
	// 誤差としてレベルアップできる秒数
	const float SAFE_TIME_SEC{ 0.04f };
	
	if (pSMFPlayer)
	{
		int currBar{ static_cast<int>(pSMFPlayer->GetPlayTime() / BAR_TIME_SEC) };

		// 1小節の区切り目
		if (currBar != prevBar_)
		{
			if (perfectTimer_ >= BAR_TIME_SEC - SAFE_TIME_SEC)
			{
				perfectTimer_ = 0.0f;

				level_ = static_cast<CloudLevel>(level_ + 1);  // レベルアップ
				if (level_ >= CLOUD_LEVEL_MAX)
				{
					level_ = static_cast<CloudLevel>(CLOUD_LEVEL_MAX - 1);
				}
				else
				{
					pMiniCharaManager->LevelUp(level_);
				}
			}
			else if (perfectTimer_ < 0.0f)
			{
				perfectTimer_ = 0;

				level_ = static_cast<CloudLevel>(level_ - 1);  // レベルダウン
				if (level_ < 0)
				{
					level_ = static_cast<CloudLevel>(0);
				}

				if (level_ > 0)
				{
					pMiniCharaManager->LevelDown(level_);
				}
			}
		}

		prevBar_ = currBar;
	}
#pragma endregion

#pragma region X座標移動処理
	Vector3 position{ pPlayer->Transform().GetPosition() };
	position.z += dropDistanceZ_;
	position.y = pStageLine->GetPosY(position) + offsetHeight_;
	Transform().SetPosition(position);
#pragma endregion

#pragma region 投下したプレゼントの処理
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
#pragma endregion

#pragma region パーフェクトタイマの更新
	PerfectTimer* pPerfectTimerUI{ FindGameObject<PerfectTimer>(perfectTimerUI_) };
	pPerfectTimerUI->SetRatio(perfectTimer_ / BAR_TIME_SEC);
#pragma endregion
}

void DropCloud::Release()
{
}
