#include "pch\pch.h"
#include "Player.h"

using namespace wtgb;

Player::Player(const EntityId _parentId, const Vector3 _localPos) :
	GameObject{ "Player.json" },
	playerTargetting_{},
	angle_{},
	awakeTimeLeft_{}
{
	Property().SetParent(_parentId);
	Transform().SetPosition(_localPos);

	RigidBody& rb{ GetComponent<RigidBody>() };
	rb.SetUseGravity(false);  // シーン読み込み直後のラグを待つために重力無効化
}

Player::~Player()
{
}

void Player::OnLoadParam(const json& _json)
{
	awakeTimeLeft_ = SafeGet<float>(_json, "awakeTimeSec");
	toTargetTime_ = SafeGet<float>(_json, "toTargetTime");
}

void Player::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());

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
