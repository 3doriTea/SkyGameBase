#include "pch\pch.h"
#include "Player.h"
#include "PlayScene.h"

#include "State/PlayState.h"
#include "SpeedController.h"
#include "BallSphere.h"

#include "../Systems/ConstantBufferSender.h"
#include "../Systems/ConstantBufferSender/PlayerConstantBuffer.h"

#include "Particle/Splat.h"

using namespace wtgb;

Player::Player(const EntityId _parentId, const Vector3 _localPos, const EntityId _playState) :
	GameObject{ "Player.json" },
	playerTargeting_{},
	angle_{ 0.0f },
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
	boundYAnim{},
	aboutCircleThreshold_{},
	autoRotation_{}
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
	// JSONから各パラメータを読み込んでいく

	awakeTimeLeft_ = SafeGet<float>(_json, "awakeTimeSec");
	toTargetTime_ = SafeGet<float>(_json, "toTargetTime");
	startLineZ_ = SafeGet<float>(_json, "startLineZ");
	slideVeloDampingPerSec_ = SafeGet<float>(_json, "slideVeloDampingPerSec");
	bounceRotationVZDiv_ = SafeGet<float>(_json, "bounceRotationVZDiv");
	onGroundRotationVelo_ = SafeGet<float>(_json, "onGroundRotationVelo");
	colliderRadius_ = SafeGet<float>(_json, "colliderRadius");
	startDushForce_ = SafeGet<float>(_json, "startDushForce");
	aboutCircleThreshold_ = SafeGet<float>(_json, "aboutCircleThreshold");
	
	boundXAnim.totalTime = SafeGet<float>(_json, "/boundXAnim/totalTime"_json_pointer);
	boundXAnim.beginScaleX = SafeGet<float>(_json, "/boundXAnim/beginScaleX"_json_pointer);
	boundXAnim.playTime = boundXAnim.totalTime;
	
	boundYAnim.totalTime = SafeGet<float>(_json, "/boundYAnim/totalTime"_json_pointer);
	boundYAnim.beginScaleY = SafeGet<float>(_json, "/boundYAnim/beginScaleY"_json_pointer);
	boundYAnim.playTime = boundYAnim.totalTime;

	autoRotation_.rotationThresholdVelocityX = SafeGet<float>(_json, "/autoRotation/rotationThresholdVelocityX"_json_pointer);
	autoRotation_.keepStandSafeAngle = SafeGet<float>(_json, "/autoRotation/keepStandSafeAngle"_json_pointer);
	autoRotation_.addTorqueX = SafeGet<float>(_json, "/autoRotation/addTorqueX"_json_pointer);

	splat.addVelocity = SafeGet<Vector3>(_json, "/splat/addVelocity"_json_pointer);
	splat.mulVelocity = SafeGet<Vector3>(_json, "/splat/mulVelocity"_json_pointer);
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

	// 一気に加速！
	rb.AddVelocity(Vector3::Forward() * startDushForce_);
	rb.SetUseGravity(true);  // 重力の影響を受けるようにする
}

void Player::Update()
{
	// シーン読み込み直後のカウントダウンを待つ
	if (WaitingCountDown())
	{
		return;  // カウントダウンを待っているなら以下無視
	}
	
	PlayState* playState{ dynamic_cast<PlayState*>(FindGameObject(playState_)) };
	if (playState && playState->GetState() == PlayState::Type::StartLine)
	{
		if (Transform().GetPosition().z > startLineZ_)
		{
			playState->ChangeState(PlayState::Type::Falling);
		}
	}

	// 地面に当たった時に回転のアニメーション
	if (GroundBounceRotation())
	{
		// 地面に当たったときのアニメーションをするならここ
		Vector3 position{ Transform().GetPosition() };
		Vector3 velocity{ GetComponent<RigidBody>().GetVelocity() };

		velocity = velocity * splat.mulVelocity;
		velocity = velocity + splat.addVelocity;

		// エフェクトを正面に飛ばす角度
		const float FORCE_ANGLE_DEG{ 15.0f };
		const float FORCE_DENSITY_ANGLE_DEG{ 1.0f };

		// エフェクトを出していく
		for (
			float rad = Mathf::ToRadian(FORCE_ANGLE_DEG / -2.0f);
			rad < Mathf::ToRadian(FORCE_ANGLE_DEG / 2.0f);
			rad += Mathf::ToRadian(FORCE_DENSITY_ANGLE_DEG))
		{
			Matrix4x4 rotation{ DirectX::XMMatrixRotationRollPitchYaw(0.0f, rad, 0.0f) };
			GetScene()->Instantiate<Splat>(
				position,
				DirectX::XMVector3Transform(velocity, rotation));
		}
	}

	AutoRotation();

	// プレイヤーを範囲外に出さないための演算
	if (OutBounce())
	{
		// バウンド時のアニメーション
		boundXAnim.playTime = 0.0f;
	}

	UpdateAnim();

	SendConstantBuffer();
}

bool Player::WaitingCountDown()
{
	const float DT{ System().Get<GameTime>().GetDeltaTime() };

	// カウントダウンを待つ
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

void Player::AutoRotation()
{
	const float DT{ System().Get<GameTime>().GetDeltaTime() };
	RigidBody& rb{ GetComponent<RigidBody>() };
	const Vector3 ROTATION{ Transform().GetRotation() };
	Transform().SetRotation(
		{
			std::fmodf(ROTATION.x, DirectX::XM_2PI),
			std::fmodf(ROTATION.y, DirectX::XM_2PI),
			std::fmodf(ROTATION.z, DirectX::XM_2PI),
		});

	Vector3 angularV{ rb.GetAngularVelocity() };

	if (angularV.x > autoRotation_.rotationThresholdVelocityX)
	{
		// 起動する速度まで低下していないなら以下無視
		return;
	}

	if (std::fabsf(ROTATION.x) < autoRotation_.keepStandSafeAngle * 0.5f)
	{
		// 直立判定内なら無視
		return;
	}

	// 中の猫の向きが苦しそうなら補正してあげる
	std::partial_ordering sign{ ROTATION.x <=> 0 };

	if (sign < 0)
	{
		// 仰向けなら前方向に加速
		rb.AddTorque(Vector3::Right() * (autoRotation_.addTorqueX));
	}
	else if (sign > 0)
	{
		// うつ伏せなら後ろ方向に加速
		rb.AddTorque(Vector3::Right() * (-autoRotation_.addTorqueX));
	}
	else if (sign == 0)
	{
		// ちょうどいいなら何もしない
	}
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

void Player::SendConstantBuffer()
{
	System().Get<ConstantBufferSender>().SendConstant<PlayerConstantBuffer>(
		[this](PlayerConstantBuffer* pConstantBuffer)
		{
			Vector3 position{ Transform().GetPosition() };
			pConstantBuffer->Ref().position = Vector4{position};
		},
		System());
}

bool Player::UpdateAnim()
{
	const float DT{ System().Get<GameTime>().GetDeltaTime() };

	bool isPlayed{ false };

#pragma region 横軸アニメーション
	if (boundXAnim.playTime < boundXAnim.totalTime)
	{
		boundXAnim.playTime += DT;
		if (boundXAnim.playTime > boundXAnim.totalTime)
		{
			boundXAnim.playTime = boundXAnim.totalTime;
		}
		isPlayed = true;  // アニメーション再生があった
	}

	float animRatioX{ boundXAnim.playTime / boundXAnim.totalTime };
	
	float scaleX
	{
		Mathf::Lerp(boundXAnim.beginScaleX, 1.0f, animRatioX)
	};
#pragma endregion

#pragma region 縦軸アニメーション
	if (boundYAnim.playTime < boundYAnim.totalTime)
	{
		boundYAnim.playTime += DT;
		if (boundYAnim.playTime > boundYAnim.totalTime)
		{
			boundYAnim.playTime = boundYAnim.totalTime;
		}
		isPlayed = true;  // アニメーション再生があった
	}

	float animRatioY{ boundYAnim.playTime / boundYAnim.totalTime };

	float scaleY
	{
		Mathf::Lerp(boundYAnim.beginScaleY, 1.0f, animRatioY)
	};
#pragma endregion

	Transform().SetScale(Vector3{ scaleX, scaleY, 1.0f });
	
	return isPlayed;
}
