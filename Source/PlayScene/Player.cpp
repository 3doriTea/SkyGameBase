#include "pch\pch.h"
#include "Player.h"
#include "PlayScene.h"

#include "State/PlayState.h"
#include "SpeedController.h"
#include "BallSphere.h"


using namespace wtgb;

Player::Player(const EntityId _parentId, const Vector3 _localPos, const EntityId _playState) :
	GameObject{ "Player.json" },
	playerTargeting_{},
	angle_{},
	awakeTimeLeft_{},
	playState_{ _playState },
	isTargeting_{ false },
	startLineZ_{},
	toTargetTime_{},
	slideVelocityX_{ 0.0f },
	bounceRotationVZDiv_{},
	rotateBoostSpeedX_{},
	onGroundRotationVelo_{},
	colliderRadius_{},
	slideVeloDampingPerSec_{},
	startDushForce_{},
	boundXAnim{},
	aboutCircleThreshold_{}
{
	Property().SetParent(_parentId);
	Transform().SetPosition(_localPos);

	RigidBody& rb{ GetComponent<RigidBody>() };
	rb.SetUseGravity(false);  // シーン読み込み直後のカウントダウンを待つために重力無効化

	PlayScene* pPlayScene{ GetScene<PlayScene>() };
	wassert(pPlayScene && "プレイシーンの取得に失敗");
	if (pPlayScene == nullptr)
	{
		return;  // プレイシーンの取得に失敗したため無視せざる終えない
	}

	// 乗るためのボールを出現させる
	pPlayScene->Instantiate<BallSphere>(GetEntityId());
}

void Player::OnLoadParam(const json& _json)
{
	awakeTimeLeft_ = SafeGet<float>(_json, "awakeTimeSec");
	toTargetTime_ = SafeGet<float>(_json, "toTargetTime");
	startLineZ_ = SafeGet<float>(_json, "startLineZ");
	slideVeloDampingPerSec_ = SafeGet<float>(_json, "slideVeloDampingPerSec");
	bounceRotationVZDiv_ = SafeGet<float>(_json, "bounceRotationVZDiv");
	onGroundRotationVelo_ = SafeGet<float>(_json, "onGroundRotationVelo");
	colliderRadius_ = SafeGet<float>(_json, "colliderRadius");
	startDushForce_ = SafeGet<float>(_json, "startDushForce");
	aboutCircleThreshold_ = SafeGet<float>(_json, "aboutCircleThreshold");
	boundXAnim.totalTime = SafeGet<float>(_json, "/boundXAnim/totalTime");
}

void Player::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());

	Collider& collider{ GetComponent<Collider>() };
	collider.SetRadius(colliderRadius_);

	angle_ = 0.0f;
}

void Player::OnStart()
{
	RigidBody& rb{ GetComponent<RigidBody>() };

	rb.SetUseGravity(true);  // 重力の影響を受けるようにする
	// 一気に加速！
	rb.AddVelocity(Vector3::Forward() * startDushForce_);
}

void Player::Update()
{
	// シーン読み込み直後のカウントダウンを待つ
	if (HasWaitingCountDown())
	{
		return;  // カウントダウンを待っているなら以下無視
	}
	
	const Input::InputGetter& input{ System().Get<Input>().Getter() };

	PlayState* playState{ dynamic_cast<PlayState*>(FindGameObject(playState_)) };
	if (playState && playState->GetState() == PlayState::Type::StartLine)
	{
		if (Transform().GetPosition().z > startLineZ_)
		{
			playState->ChangeState(PlayState::Type::Falling);
		}
	}

	if (GroundBounceRotation())
	{
		// 地面に当たったときのアニメーションをするならここ
	}

	// プレイヤーを範囲外に出さないための演算
	if (OutBounce())
	{
		// バウンド時のアニメーションするならここ
	}

	UpdateAnim();
}

bool Player::HasWaitingCountDown()
{
	const float DT{ System().Get<GameTime>().GetDeltaTime() };

	if (awakeTimeLeft_ > 0.0f)
	{
		awakeTimeLeft_ -= DT;
		if (awakeTimeLeft_ <= 0.0f)
		{
			OnStart();
		}
		return true;
	}

	return false;
}

bool Player::GroundBounceRotation()
{
	RigidBody& rb{ GetComponent<RigidBody>() };


	bool isBounce{ false };  // バウンドしたか
	std::vector<Collider*> hitColliders{};
	rb.GetHitColliders(&hitColliders);

	for (Collider* pColl : hitColliders)
	{
		if (pColl && pColl->GetColliderType() == Collider::Type::Section)
		{
			Vector3 angularVelo{ rb.GetAngularVelocity() };
			if (angularVelo.x < onGroundRotationVelo_)
			{
				// まだ最低回転速度に達していないなら回転速度をかける

				Vector3 velo{ rb.GetVelocity() };
				rb.AddTorque({ velo.z / bounceRotationVZDiv_, 0.0f, 0.0f });
				isBounce = true;
			}
		}
	}

	return isBounce;
}

bool Player::OutBounce()
{
	PlayScene* pPlayScene{ GetScene<PlayScene>() };
	if (pPlayScene == nullptr)
	{
		return false;  // プレイシーンの取得ができなければ以下無視
	}
	const float DT{ System().Get<GameTime>().GetDeltaTime() };
	RigidBody& rb{ GetComponent<RigidBody>() };
	WorldConfig worldConfig{ pPlayScene->GetWorldConfig() };


	Vector3 v{ rb.GetVelocity() };
	Vector3 pos{ Transform().GetPosition() };

	bool isBounced{ false };  // バウンドしたか

	if ((pos.x < worldConfig.safeZoneXMin && v.x < 0)
		|| (pos.x > worldConfig.safeZoneXMax && v.x > 0))
	{
		v.x *= -1.0f;
		isBounced = true;
	}

	float vv = std::powf(slideVeloDampingPerSec_, DT);
	v.x *= vv;
	rb.SetVelocity(v);

	return isBounced;
}

void Player::AddMove(const Vector3 _move)
{
	float DT{ System().Get<GameTime>().GetDeltaTime() };
	RigidBody& rb{ GetComponent<RigidBody>() };

	if (TryFocusToCharaEgg())
	{
		return;  // キャラエッグへのフォーカス処理があったなら無視
	}

	// 特に何もないならそのまま加速
	rb.AddVelocity(_move);
}

bool Player::TryFocusToCharaEgg()
{
	using namespace DirectX;

	Camera& camera{ System().Get<Camera>() };
	Vector3 selfPos{ Transform().GetPosition() };
	Vector3 selfDir{ camera.GetDirection() };
	RigidBody& rb{ GetComponent<RigidBody>() };

	std::vector<GameObject*> foundGameObjects{};
	if (FindGameObjects("CharaEgg", &foundGameObjects))
	{
		GameObject* pMostCloseCharaEgg{ nullptr };  // 最も近いキャラエッグ
		float mostCloseDistanceD{ FLT_MAX };        // 最も近いキャラエッグとの距離
		float mostCloseDot{ 0.0f };                 // 最も近いキャラエッグとのcos値
		Vector3 mostClosePosition{};                // 最も近いキャラエッグの座標

		for (GameObject* pCharaEgg : foundGameObjects)
		{
			Vector3 eggPos{ pCharaEgg->Transform().GetPosition() };
			Vector3 toDir{ XMVector3Normalize(eggPos - selfPos) };

			if (toDir.z <= 0.0f)
			{
				continue;  // プレイヤーより後ろにいるのは無視
			}

			float dot{ XMVectorGetX(XMVector3Dot(selfDir, toDir)) };

			// 大まかなに円に触れている
			if (dot > aboutCircleThreshold_)
			{
				float distanceD  // 距離の2乗
				{
					DirectX::XMVectorGetX(
						DirectX::XMVector3LengthSq(toDir))
				};

				auto pickUp  // 選択中のキャラエッグを選ぶ
				{
					[&]
					{
						pMostCloseCharaEgg = pCharaEgg;
						mostCloseDistanceD = distanceD;
						mostCloseDot = dot;
						mostClosePosition = eggPos;
					}
				};

				// 距離の差分
				const float EQUAL_THRESHOLD{ 1.0f };
				float distanceDiff{ distanceD - mostCloseDistanceD };
				if (distanceDiff < -EQUAL_THRESHOLD)  // 確実に小さい
				{
					pickUp();
				}
				else if (distanceDiff < EQUAL_THRESHOLD)  // ほぼ距離が一緒
				{
					// ほぼ距離が同じなら最も円の中心に近い方を選ぶ
					if (dot > mostCloseDot)  // 1に近いほど
					{
						pickUp();
					}
				}
			}
		}

		// 見つかったなら
		if (pMostCloseCharaEgg)
		{
			PlayScene* pPlayScene{ GetScene<PlayScene>() };
			wassert(pPlayScene && "プレイシーンの取得に失敗");

			float gravity{};
			if (pPlayScene)
			{
				gravity = pPlayScene->GetWorldConfig().gravity;
			}
			Vector3 v
			{
				playerTargeting_.GetToTargetVelocity(
				{
					.playerPos = selfPos,
					.playerVelocity = rb.GetVelocity(),
					.targetPos = mostClosePosition,
					.gravity = gravity
				})
			};
			rb.SetVelocity(v);
			return true;  // フォーカス処理行う
		}
	}
	return false;  // フォーカス処理行わず
}

bool Player::UpdateAnim()
{
	const float DT{ System().Get<GameTime>().GetDeltaTime() };

	if (boundXAnim.playTime < boundXAnim.totalTime)
	{
		boundXAnim.playTime += DT;
		if (boundXAnim.playTime > boundXAnim.totalTime)
		{
			boundXAnim.playTime = boundXAnim.totalTime;
		}
		return true;  // アニメーション再生があった
	}

	return false;
}
