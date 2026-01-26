#include "pch\pch.h"
#include "Player.h"
#include "PlayScene.h"

#include "PlayState.h"
#include "SpeedController.h"
#include "BallSphere.h"


using namespace wtgb;

Player::Player(const EntityId _parentId, const Vector3 _localPos, const EntityId _playState) :
	GameObject{ "Player.json" },
	playerTargetting_{},
	angle_{},
	awakeTimeLeft_{},
	playState_{ _playState },
	speedController_{ INVALID_ENTITY },
	isTargetting_{ false },
	startLineZ_{},
	toTargetTime_{}
{
	Property().SetParent(_parentId);
	Transform().SetPosition(_localPos);

	RigidBody& rb{ GetComponent<RigidBody>() };
	rb.SetUseGravity(false);  // シーン読み込み直後のラグを待つために重力無効化

	// 乗るためのボールを出現させる
	GetScene().Instantiate<BallSphere>(GetEntityId());
}

Player::~Player()
{
}

void Player::OnLoadParam(const json& _json)
{
	awakeTimeLeft_ = SafeGet<float>(_json, "awakeTimeSec");
	toTargetTime_ = SafeGet<float>(_json, "toTargetTime");
	startLineZ_ = SafeGet<float>(_json, "startLineZ");
}

void Player::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());

	speedController_ = GetScene<PlayScene>().Instantiate<SpeedController>();

	Collider& collider{ GetComponent<Collider>() };

	collider.SetRadius(2.0f);

	angle_ = 0.0f;
	//GetComponent<ModelMesh>().Load();
}

void Player::Update()
{
	float dt{ System().Get<GameTime>().GetDeltaTime() };
	const Input::InputGetter& input{ System().Get<Input>().Getter() };
	RigidBody& rb{ GetComponent<RigidBody>() };
	WorldConfig worldConfig{ GetScene<PlayScene>().GetWorldConfig()};

	// シーン読み込み直後のラグを待つ
	if (awakeTimeLeft_ > 0.0f)
	{
		awakeTimeLeft_ -= dt;
		if (awakeTimeLeft_ <= 0.0f)
		{
			rb.SetUseGravity(true);  // 重力の影響を受けるようにする
		}
		return;
	}

	// スピードを設定する
	SpeedController* pSpeedController
	{
		dynamic_cast<SpeedController*>(FindGameObject(speedController_))
	};
	pSpeedController->SetSpeed(rb.GetVelocity().z);

	PlayState* playState{ dynamic_cast<PlayState*>(FindGameObject(playState_)) };
	if (playState && playState->GetState() == PlayState::Type::StartLine)
	{
		if (Transform().GetPosition().z > startLineZ_)
		{
			playState->ChangeState(PlayState::Type::Falling);
		}
	}

	if (input.IsKeyDown(KeyCode::Space))
	{
		rb.AddVelocity({ 0.0f, -500.0f, 0.0f });
	}

	std::vector<Collider*> hitColliders{};
	rb.GetHitColliders(&hitColliders);

	for (Collider* pColl : hitColliders)
	{
		if (pColl && pColl->GetColliderType() == Collider::Type::Section)
		{
			rb.AddTorque({ 0.03f, 0.0f, 0.0f });
		}
	}

	// MEMO: 簡易的ジャンプ
	if (input.IsKeyDown(KeyCode::Space))
	{
		rb.AddVelocity({ 0.0f, 3.0f, 0.0f });
	}

	// プレイヤーを範囲外に出さないための演算
	Vector3 v{ rb.GetVelocity() };
	Vector3 pos{ Transform().GetPosition() };
	if ((pos.x < worldConfig.safeZoneXMin && v.x < 0)
		|| (pos.x > worldConfig.safeZoneXMax && v.x > 0))
	{
		v.x *= -1.0f;
		rb.SetVelocity(v);
	}

	return;

	angle_ += DirectX::XM_2PI / 10.0f * dt;
	if (angle_ >= DirectX::XM_2PI)
	{
		angle_ -= DirectX::XM_2PI;
	}

	Vector3 rotation{ Transform().GetRotation() };
	rotation.y = angle_;
	Transform().SetRotation(rotation);

	Transform().SetScale((std::sinf(angle_) * std::sinf(angle_) * 3.0f) * Vector3::One() + Vector3::One());
}

void Player::AddMove(const Vector3 _move)
{
	using namespace DirectX;

	Camera& camera{ System().Get<Camera>() };
	float dt{ System().Get<GameTime>().GetDeltaTime() };
	RigidBody& rb{ GetComponent<RigidBody>() };

	Vector3 selfPos{ Transform().GetPosition() };
	Vector3 selfDir{ camera.GetDirection() };


	std::vector<GameObject*> foundGameObjects{};
	if (FindGameObjects("CharaEgg", &foundGameObjects))
	//if (false)
	{
		for (GameObject* pCharaEgg : foundGameObjects)
		{
			Vector3 eggPos{ pCharaEgg->Transform().GetPosition() };
			Vector3 toDir{ XMVector3Normalize(eggPos - selfPos) };

			float dot{ XMVectorGetX(XMVector3Dot(selfDir, toDir)) };

			if (dot > 0.99f)
			{
				Vector3 v
				{
					playerTargetting_.GetToTargetVelocity(
					{
						.playerPos = selfPos,
						.playerVelocity = rb.GetVelocity(),
						.targetPos = eggPos,
						.gravity = 9.8f
					})
				};
				rb.SetVelocity(v);
				return;  // 速度を適用して回帰
			}
		}
	}

	rb.AddVelocity(_move);
}

const ISpeedController* Player::GetSpeedController()
{
	return dynamic_cast<const ISpeedController*>(FindGameObject(speedController_));
}
