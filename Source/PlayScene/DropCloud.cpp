#include "pch\pch.h"
#include "DropCloud.h"
#include "Player.h"
#include "StageLine.h"
#include "SMF/SMFPlayer.h"
#include "PlayScene.h"
#include "PresentSphere.h"
#include "State/PlayState.h"
#include "GoalGround.h"
#include "ResultScene/ResultScene.h"
#include "ISpeedController.h"


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
	speedController_{ _speedController }
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

		// ノーツ再生時の音源読み込み && セット
		pSMFPlayer->SetToneAudioHandle(
			audio.Load(playToneAudioFilePath_));

		// ノーツの処理を登録
		pSMFPlayer->OnNote([this, pSMFPlayer, pStageLine](Note _note)
			{
				PlayScene* pPlayScene{ GetScene<PlayScene>() };
				if (pPlayScene == nullptr)
				{
					return;  // プレイシーンが取得できなければ何もしない
				}

				if (_note.channel == 0x03)
				{
					droppedPresents_.push_back(DroppedPresent
						{
							.entityId = pPlayScene->Instantiate<PresentSphere>(
								player_,
								Transform().GetPosition(),
								Vector3{ Transform().GetPosition().x, pStageLine->GetPosY(Transform().GetPosition()), Transform().GetPosition().z }),
							.note = _note,
						});
				}
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
	wassert(pSMFPlayer && "SMFPlayerが見つからなかった");
	Player* pPlayer{ FindGameObject<Player>(player_) };
	wassert(pPlayer && "プレイヤーが見つからなかった");
	StageLine* pStageLine{ FindGameObject<StageLine>(stageLine_) };
	wassert(pStageLine && "ステージラインが見つからなかった");
	ISpeedController* pSpeedController{ FindGameObject<ISpeedController>(speedController_) };
	wassert(pSpeedController && "スピードコントローラが見つからなかった");


#pragma region 再生が終了したら1回だけゴール処理
	if (pSMFPlayer
		&& isFinished_ == false
		&& pSMFPlayer->IsFinished())
	//if (System().Get<Input>().Getter().IsKeyDown(KeyCode::H))
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

	Vector3 velocity{ playerRigidBody.GetVelocity() };

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
			break;
		case SpeedType::Good:
			// 十分スピードがあるなら通常再生
			playRate = 1.0f;
			break;
		case SpeedType::Excissive:
		default:
			break;
		}
		pSMFPlayer->SetPlayRate(playRate);
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
			pSMFPlayer->PlayTone(itr->note);
		}

		itr++;
	}
}

void DropCloud::Release()
{
}
