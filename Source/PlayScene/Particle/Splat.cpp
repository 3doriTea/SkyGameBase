#include "Splat.h"

Splat::Splat(const Vector3 _position, const Vector3 _velocity) :
	GameObject{ "Play/Particle/Splat.json" }
{
	Transform().SetPosition(_position);
	GetComponent<RigidBody>().AddVelocity(_velocity);
}

Splat::~Splat()
{
}

void Splat::Init()
{
}

void Splat::Update()
{
	const float LESS_SIZE_PER_SEC{ 0.1f };       // 自然に小さくなる1秒間当たりの量
	const float LESS_SIZE_BOUNDED{ 0.3f };       // バウンドした時に小さくなる量
	const float DESTROY_SIZE_THRESHOLD{ 0.1f };  // 見えないと判断する大きさ
	
	Vector3 scale = Transform().GetScale();

	// 自然に小さくなっていく
	scale = scale
		- Vector3::One()
		* (LESS_SIZE_PER_SEC * System().Get<GameTime>().GetDeltaTime());

	// 何かしらに当たったならさらに小さくしていく
	if (GetComponent<RigidBody>().IsHit())
	{
		scale = scale - Vector3::One() * LESS_SIZE_BOUNDED;
	}

	if (scale.x < DESTROY_SIZE_THRESHOLD)  // 小さすぎるなら消す
	{
		Transform().SetScale(Vector3::Zero());
		DestroyMe();
	}
	else
	{
		Transform().SetScale(scale);
	}
}

void Splat::Release()
{
}
