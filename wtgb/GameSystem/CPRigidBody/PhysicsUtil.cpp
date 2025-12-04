#include "pch\pch.h"
#include "PhysicsUtil.h"
#include "GameComponent/Collider.h"
#include "GameComponent/Transform.h"
#include "GameComponent/RigidBody.h"
#include "WTGBAssert.h"

#include "GameSystem/Debug.h"

using DirectX::XMVector3TransformCoord;
//using DirectX::XMVector3Length;
using DirectX::XMVector3LengthSq;  // 計算を省く
using DirectX::XMVector3TransformCoordStream;
using DirectX::XMMatrixInverse;

using DirectX::XMFLOAT3;

namespace
{
	// 同時と判定する時間差 (秒)
	const float SIMULTANEOUS_THRESHOLD_SEC{ 1.0f };
}

bool wtgb::PhysicsUtil::IsHit(ColliderSet* _pSelf, ColliderSet* _pOther)
{
	switch (_pSelf->pCollider->GetColliderType())
	{
	case Collider::Type::Section:
		break;
	case Collider::Type::Sphere:
		break;
	default:
		break;
	}

	return false;
}

bool wtgb::PhysicsUtil::IsHitFromSection(ColliderSet* _pSelfSection, ColliderSet* _pOther, CollisionInfo* _pCollisionInfo)
{
	wassert(_pSelfSection->pCollider->GetColliderType() == Collider::Type::Section
		&& "自身のコライダーはセクションである必要がある");

	if (_pSelfSection->pCollider->GetColliderType() != Collider::Type::Section)
	{
		// 自身のコライダーが不一致
		return IsHit(_pSelfSection, _pOther);
	}

	switch (_pOther->pCollider->GetColliderType())
	{
	case Collider::Type::Sphere:
	{
		Matrix4x4 toLocalMatrix
		{
			XMMatrixInverse(
				nullptr,
				_pOther->pTransform->GetWorldMatrix()
				* XMMatrixInverse(nullptr, _pOther->pTransform->GetLocalMatrix()))
		};
		Vector3 localCenter{ XMVector3TransformCoord(_pOther->pCollider->sphere.center, toLocalMatrix) };
		
		std::vector<Vector2>& points{ _pSelfSection->pCollider->section.points2D };
		
		float radius{ _pOther->pCollider->sphere.radius };
		Vector2 circle{ localCenter.z, localCenter.y };
		
		for (int i = 0; i < points.size() - 1; i++)
		{
			const Vector2 S{ points[i + 1] - points[i] };
			const Vector2 A{ circle - points[i] };

			using namespace DirectX;

			if (XMVector2Cross(S, A).m128_f32[0] < 0)
			{
				return true;  // 下にいる
			}

			const Vector2 B{ circle - points[i + 1] };
			if (std::fabsf(XMVector2Cross(S, A).m128_f32[0]) / XMVector2Length(S).m128_f32[0] <= radius)
			{
				if (XMVector2Cross(XMVector2Dot(A, S), XMVector2Dot(B, S)).m128_f32[0] > 0)
				{
					// 線分が当たった
					return true;
				}
				else
				{
					if (radius > XMVector2Length(A).m128_f32[0]
						|| radius > XMVector2Length(B).m128_f32[0])
					{
						// 線分が当たった
						return true;
					}
				}
			}
		}

		/*
		std::vector<XMFLOAT3> localPoints;

		for (auto& point : _pSelfSection->pCollider->section.points2D)
		{
			localPoints.push_back({ 0.0f, point.y, point.x });
		}
		std::vector<XMFLOAT3> worldPoints(localPoints.size(), {});
		XMVector3TransformCoordStream(
			worldPoints.data(),
			sizeof(XMFLOAT3),
			localPoints.data(),
			sizeof(XMFLOAT3),
			localPoints.size(),
			_pSelfSection->pTransform->GetWorldMatrix());

		for (int i = 0; i < worldPoints.size(); i++)
		{
			worldPoints[i]
		}
		*/
		break;
	}
	case Collider::Type::Section:
		wassert(false && "セクション同士の当たり判定はできません。");
		break;
	default:
		break;
	}

	return false;
}

bool wtgb::PhysicsUtil::IsHitFromSphere(ColliderSet* _pSelfSphere, ColliderSet* _pOther, CollisionInfo* _pCollisionInfo)
{
#pragma region コライダーセット確認
	if (!_pSelfSphere || !_pOther)
	{
		wassert(false && "コライダセットがnullptrだった");
		return false;
	}

	if (_pSelfSphere == _pOther)
	{
		wassert(false && "自身と相手のコライダセットが同じ");
		return false;
	}

	if (!_pSelfSphere->pCollider || !_pOther->pCollider)
	{
		wassert(false && "コライダがnullptrだった");
		return false;
	}

	if (_pSelfSphere->pCollider == _pOther->pCollider)
	{
		wassert(false && "自身と相手のコライダが同じ");
		return false;
	}

	wassert(_pSelfSphere->pTransform != _pOther->pTransform && "Transform一緒だった");

	wassert(_pSelfSphere->pCollider->GetColliderType() == Collider::Type::Sphere
		&& "自身のコライダーは球である必要がある");

	if (_pSelfSphere->pCollider->GetColliderType() != Collider::Type::Sphere)
	{
		// 自身のコライダーが不一致
		return IsHit(_pSelfSphere, _pOther);
	}
#pragma endregion

	switch (_pOther->pCollider->GetColliderType())
	{
	case Collider::Type::Section:
		return IsHitSphereVSSection(_pSelfSphere, _pOther, _pCollisionInfo);
	case Collider::Type::Sphere:
		return IsHitSphereVSSphere(_pSelfSphere, _pOther, _pCollisionInfo);
	default:
		break;
	}

	return false;
}

/// <summary>
/// 動く円
/// </summary>
struct CircleBody
{
	wtgb::Vector2 center;      // 円の中心座標
	wtgb::Vector2 velocity;    // 速度
	float radius;              // 半径
};

/// <summary>
/// 断面地形
/// </summary>
struct Section
{
	wtgb::Vector2 begin;  // 始点
	wtgb::Vector2 end;    // 終点
};

void CircleBodyVSSegment(
	const CircleBody& _circleBody,
	const Section& _section,
	wtgb::CollisionInfo* _pCollisionInfo)
{
	using namespace wtgb;
	using namespace DirectX;

	CollisionInfo info{};
	info.time = FLT_MAX;  // 当たらないなら当たるまでの時間は無限にしておく

	// まずは次のフレームで当たっているか
	const Vector2 CURR_CENTER{ _circleBody.center };
	const Vector2 NEXT_CENTER{ CURR_CENTER + _circleBody.velocity };

#pragma region 絶対に当たらない場合除外
	const float CIRCLE_MAX_X{ max(CURR_CENTER.x, NEXT_CENTER.x) + (_circleBody.radius * 2.0f) };
	const float CIRCLE_MIN_X{ min(CURR_CENTER.x, NEXT_CENTER.x) - (_circleBody.radius * 2.0f) };

	if (CIRCLE_MAX_X < _section.begin.x || _section.end.x < CIRCLE_MIN_X)
	{
		info.isHit = false;
		info.isIgnoreFar = true;
	}
#pragma endregion

	// 線分ベクトル
	const Vector2 V{ _section.end - _section.begin };
	// 線分始点から円の中心
	const Vector2 W{ _circleBody.center - _section.begin };
	// 円の半径の2乗
	const float RADIUS_SQ{ _circleBody.radius * _circleBody.radius };

	// 線分の長さの2乗
	const float SEGMENT_LENGTH_SQ{ XMVectorGetX(XMVector2LengthSq(V)) };

	// 最近接点
	Vector2 point2D{};

	// 線分がもうほぼ点と言って過言ではない
	if (SEGMENT_LENGTH_SQ < FLT_EPSILON)
	{
		point2D = _section.begin;

		// 埋め込み具合
		info.depth = RADIUS_SQ - XMVectorGetX(XMVector2LengthSq(W));

		// なら点と円の当たり判定
		info.isHit = info.depth >= 0.0f;
	}
	else  // 線分としての処理
	{
		// 線分上での接点の割合
		float t{ XMVectorGetX(XMVector2Dot(W, V)) / SEGMENT_LENGTH_SQ };

		if (t < 0.0f)  // 始点より前にある
		{
			point2D = _section.begin;
		}
		else if (t > 1.0f)  // 終点より後にある
		{
			point2D = _section.end;
		}
		else  // 線分の間
		{
			point2D = V * t + _section.begin;
		}

		// 円の中心から最近接点への距離の2乗
		const float DISTANCE_SQ{ XMVectorGetX(XMVector2LengthSq(point2D - NEXT_CENTER)) };

		// 埋め込み具合
		info.depth = std::sqrtf(RADIUS_SQ) - std::sqrtf(DISTANCE_SQ);

		// なら点と円の当たり判定
		info.isHit = DISTANCE_SQ <= RADIUS_SQ;
	}

	info.hitPoint = { 0.0f, point2D.y, point2D.x };

	if (info.isHit)
	{
		// 当たっているなら押し出しと時刻を返す
		Vector2 push2D{};


		// 1フレームで移動
		const Vector2 MOVE{ NEXT_CENTER - CURR_CENTER };
		
		// 円の中心から最近接点
		const Vector2 CENTER_TO_POINT{ point2D - CURR_CENTER };

		// 反発する方向
		Vector2 retDir{ XMVector2Normalize(CENTER_TO_POINT * -1.0f) };

		if (XMVectorGetX(XMVector2LengthSq(retDir)) <= FLT_EPSILON)
		{
			retDir = Vector2::Up();
		}

		// 半径分戻すベクトル
		const Vector2 RET_RADIUS{ retDir * _circleBody.radius };

		// 半径分戻したベクトル
		const Vector2 TO_HIT_POS{ CENTER_TO_POINT + RET_RADIUS };

		// 当たることが予定されるため動かす分
		push2D = (NEXT_CENTER + TO_HIT_POS) - CURR_CENTER;

		// 当たるまでの時間を取っておく
		info.time = XMVectorGetX(XMVector2Length(MOVE - push2D));

		// 線分に垂直な法線ベクトル
		const Vector2 SEGMENT_NORM{ XMVector2Normalize(Vector2{ -V.y, V.x }) };

		// 侵入速度
		const Vector2 F{ _circleBody.velocity };

		// 反射ベクトル
		const Vector2 R{ F - 2.0f * XMVectorGetX(XMVector2Dot(F, SEGMENT_NORM)) * SEGMENT_NORM };

		info.reflectionVelocity = { 0.0f, R.y, R.x };
		info.push = { 0.0f, push2D.y, push2D.x };
	}

	// 当たり判定情報が必要なら渡す
	if (_pCollisionInfo)
	{
		*_pCollisionInfo = info;
	}
}

bool wtgb::PhysicsUtil::IsHitSphereVSSection(ColliderSet* _pSphere, ColliderSet* _pSection, CollisionInfo* _pCollisionInfo)
{
#pragma region コライダーセット確認
	using namespace DirectX;

	if (!_pSphere || !_pSection)
	{
		wassert(false && "コライダセットがnullptrだった");
		return false;
	}

	if (_pSphere == _pSection)
	{
		wassert(false && "自身と相手のコライダセットが同じ");
		return false;
	}

	if (!_pSphere->pCollider || !_pSection->pCollider)
	{
		wassert(false && "コライダがnullptrだった");
		return false;
	}

	if (_pSphere->pCollider == _pSection->pCollider)
	{
		wassert(false && "自身と相手のコライダが同じ");
		return false;
	}

	wassert(_pSphere->pTransform != _pSection->pTransform && "Transform一緒だった");

	if (_pSphere->pCollider->GetColliderType() != Collider::Type::Sphere
		|| _pSection->pCollider->GetColliderType() != Collider::Type::Section)
	{
		wassert(false && "コライダタイプが不一致");
		return false;
	}

	if (!_pSphere->pRigidBody)
	{
		wassert(false && "球のRigidBodyが指定されていない");
		return false;
	}
#pragma endregion

	// 円の中心ワールド座標
	Vector3 worldCenterPos{ XMVector3TransformCoord(_pSphere->pCollider->sphere.center, _pSphere->pTransform->GetWorldMatrix()) };
	// 線分たち
	std::vector<Vector2>& points{ _pSection->pCollider->section.points2D };
	// 円の半径
	const float RADIUS{ _pSphere->pCollider->sphere.radius };

	const Vector3 VELOCITY{ _pSphere->pRigidBody->GetVelocity() };

	float time{};
	CollisionInfo bestInfo{};
	bestInfo.time = FLT_MAX;

	CircleBody circleBody
	{
		.center = { worldCenterPos.z, worldCenterPos.y },
		.velocity = { VELOCITY.z, VELOCITY.y },
		.radius = _pSphere->pCollider->sphere.radius,
	};

	for (int i = 0; i < points.size() - 1; i++)
	{
		CollisionInfo info{};

		CircleBodyVSSegment(
			circleBody,
			Section
			{
				.begin = points[i],
				.end = points[i + 1],
			},
			&info);

		if (info.isIgnoreFar)
		{
			continue;  // 遠すぎるなら完全無視
		}

		// 接点のx座標は入っていないため入れる
		info.hitPoint.x = _pSphere->pTransform->GetPositionWorld().x;
		Debug::DrawPoint(info.hitPoint);

		if (info.isHit)  // 当たっているなら
		{
			if (bestInfo.isHit == false)
			{
				// 前の情報が当たっていないときなら必ず上書き
				bestInfo = info;
			}
			else
			{
				LOGFLN("時間差:{}", std::fabsf(info.time - bestInfo.time));

				if (std::fabsf(info.time - bestInfo.time) <= SIMULTANEOUS_THRESHOLD_SEC)  // 当たるまでの時間がほぼ同じなら
				{
					LOGF("同時に衝突");

					bestInfo.push = bestInfo.push + info.push;
					bestInfo.normal = XMVector3Normalize(bestInfo.normal + info.normal);
					// ここはハーフいらないかも？
					//bestInfo.push = XMVectorScale((bestInfo.push + info.push), 0.5f);
					bestInfo.reflectionVelocity = XMVectorScale((bestInfo.reflectionVelocity + info.reflectionVelocity), 0.5f);
				}
				else if (info.time < bestInfo.time)  // 当たるまでの時間が短い方を適用
				{
					bestInfo = info;
				}
			}
		}
	}

	if (_pCollisionInfo)
	{
		*_pCollisionInfo = bestInfo;
	}

	return bestInfo.isHit;
}

bool wtgb::PhysicsUtil::IsHitSphereVSSphere(ColliderSet* _pSphereA, ColliderSet* _pSphereB, CollisionInfo* _pCollisionInfo)
{
	using namespace DirectX;

	if (!_pSphereA || !_pSphereB)
	{
		wassert(false && "コライダセットがnullptrだった");
		return false;
	}

	if (_pSphereA == _pSphereB)
	{
		wassert(false && "自身と相手のコライダセットが同じ");
		return false;
	}

	if (!_pSphereA->pCollider || !_pSphereB->pCollider)
	{
		wassert(false && "コライダがnullptrだった");
		return false;
	}

	if (_pSphereA->pCollider == _pSphereB->pCollider)
	{
		wassert(false && "自身と相手のコライダが同じ");
		return false;
	}

	wassert(_pSphereA->pTransform != _pSphereB->pTransform && "Transform一緒だった");

	if (_pSphereA->pCollider->GetColliderType() != Collider::Type::Sphere
		|| _pSphereB->pCollider->GetColliderType() != Collider::Type::Sphere)
	{
		wassert(false && "コライダタイプが不一致");
		return false;
	}

	Vector3 selfCenterWorld{ XMVector3TransformCoord(_pSphereA->pCollider->sphere.center, _pSphereA->pTransform->GetWorldMatrix()) };
	Vector3 otherCenterWorld{ XMVector3TransformCoord(_pSphereB->pCollider->sphere.center, _pSphereB->pTransform->GetWorldMatrix()) };

	Vector3 diff{ otherCenterWorld - selfCenterWorld };

	// 距離
	float distanceSq{ XMVector3LengthSq(diff).m128_f32[0] };
	// 当たっている閾値
	float threshold{ _pSphereA->pCollider->sphere.radius + _pSphereB->pCollider->sphere.radius };
	float thresholdSq{ threshold * threshold };

	// 二乗同士で判定
	if (distanceSq <= thresholdSq)
	{
		// 当たっている
		if (_pCollisionInfo)
		{
			_pCollisionInfo->isHit = true;
			_pCollisionInfo->distance = std::sqrtf(distanceSq);
			_pCollisionInfo->normal = diff / _pCollisionInfo->distance;
			_pCollisionInfo->hitPoint = Vector3::Zero();
		}
		return true;
	}
	return false;
}

wtgb::Vector3 wtgb::PhysicsUtil::GetPush(ColliderSet* _pSelf, ColliderSet* _pOther)
{
	return Vector3();
}
