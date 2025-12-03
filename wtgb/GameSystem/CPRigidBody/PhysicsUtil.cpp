#include "pch\pch.h"
#include "PhysicsUtil.h"
#include "GameComponent/Collider.h"
#include "GameComponent/Transform.h"
#include "WTGBAssert.h"

using DirectX::XMVector3TransformCoord;
//using DirectX::XMVector3Length;
using DirectX::XMVector3LengthSq;  // 計算を省く
using DirectX::XMVector3TransformCoordStream;
using DirectX::XMMatrixInverse;

using DirectX::XMFLOAT3;

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

bool wtgb::PhysicsUtil::IsHitSphereVSSection(ColliderSet* _pSphere, ColliderSet* _pSection, CollisionInfo* _pCollisionInfo)
{
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

	// 円の中心ワールド座標
	Vector3 worldCenterPos{ XMVector3TransformCoord(_pSphere->pCollider->sphere.center, _pSphere->pTransform->GetWorldMatrix()) };
	// 線分たち
	std::vector<Vector2>& points{ _pSection->pCollider->section.points2D };
	// 円の半径
	const float RADIUS{ _pSphere->pCollider->sphere.radius };

	bool isHit{ false };
	for (int i = 0; i < points.size() - 1; i++)
	{
		// 円中心座標
		const Vector2 C{ worldCenterPos.z, worldCenterPos.y };
		// 線分始点座標
		const Vector2 P1{ points[i] };
		// 線分終点座標
		const Vector2 P2{ points[i + 1] };

		if (isHit)
		{
			// 当たっているならこの周回で最後にする
			i = static_cast<int>(points.size());

			// Z+の方向だけ半径プラスして当たり判定
			if ((C.x + RADIUS) < P1.x || P2.x < (C.x - RADIUS))
			{
				// 広めにしても当っていないなら無視
				continue;
			}
		}
		else
		{
			// yで区切ったときの区画フィルタ
			if ((C.x - RADIUS) < P1.x || P2.x < (C.x + RADIUS))
			{
				continue;  // 範囲外なら確実に当たらない
			}
		}

		// 線分ベクトル
		const Vector2 V{ P2 - P1 };
		// 始点から円中心へのベクトル
		const Vector2 W{ C - P1 };

		// 接点座標
		Vector2 p{};
		const float V_LEN_SQ{ XMVectorGetX(XMVector2LengthSq(V)) };
		if (V_LEN_SQ <= FLT_EPSILON)
		{
			p = P1;
		}
		else
		{
			float t { (W.x * V.x + W.y * V.y) / V_LEN_SQ };
			if (t < 0.0f)
			{
				t = 0.0f;
			}
			else if(t > 1.0f)
			{
				t = 1.0f;
			}
			p = P1 + Vector2{ t, t } * V;
		}

		// 接点から円中心への差分ベクトル
		const Vector2 D{ C - p };
		// 距離の2乗
		const float DIST2{ XMVectorGetX(XMVector2LengthSq(D)) };
		// 半径の2乗
		const float R2{ RADIUS * RADIUS };

		if (_pCollisionInfo)
		{
			_pCollisionInfo->hitPoint = { 0.0f, p.y, p.x };
			_pCollisionInfo->isHit = false;
			if (DIST2 > FLT_EPSILON)
			{
				_pCollisionInfo->distance = std::sqrtf(DIST2);
			}
			else
			{
				_pCollisionInfo->distance = 0.0f;
			}
			_pCollisionInfo->depth = RADIUS - _pCollisionInfo->distance;

			/*if (_pCollisionInfo->depth < 0.0f)
			{
				_pCollisionInfo->depth = -_pCollisionInfo->depth;
			}*/

			if (_pCollisionInfo->distance > FLT_EPSILON)
			{
				// 2Dから3Dへ変換する
				Vector2 normal2D{ D / _pCollisionInfo->distance };
				if (normal2D.y < 0)
				{
					normal2D.y *= -1.0f;
				}
				_pCollisionInfo->normal = { 0.0f, normal2D.y, normal2D.x };
			}
			else  // 完全に重なっちゃったときは上向きにして置く
			{
				_pCollisionInfo->normal = Vector3::Up();
			}
		}

		if (DIST2 <= R2 + FLT_EPSILON)
		{
			isHit = true;
			LOGFLN("線分に当たっている({}to{})", i, i + 1);
			if (_pCollisionInfo)
			{
				_pCollisionInfo->isHit = true;
			}
			continue;
		}

		if (C.y < min(P1.y, P2.y))
		{
			isHit = true;
			LOGFLN("区間内の下にいる({}to{})", i, i + 1);
			if (_pCollisionInfo)
			{
				_pCollisionInfo->normal = Vector3::Up();
				
				//_pCollisionInfo->depth = 
				//_pCollisionInfo->hitPoint =   // TODO: 区間内の下にいる場合、直上の座標を当たった座標にする
				_pCollisionInfo->isHit = true;
			}
			continue;
			//return true;  // 当たっている
		}

		//// 球が下にいるかフィルタ
		//if (C.y <= p.y)
		//{
		//	isHit = true;
		//	LOGFLN("下にいる");
		//	if (_pCollisionInfo)
		//	{
		//		_pCollisionInfo->normal = _pCollisionInfo->normal * -1.0f;
		//		_pCollisionInfo->isHit = true;
		//	}
		//	continue;
		//	//return true;  // 埋まっているなら当たっている
		//}

		// 線分に垂直な上方向ベクトル
		Vector2 vertical{ -V.y, V.x };

		// 垂直な上方向ベクトルと球へのベクトルの内積で上下判定
		/*if (XMVectorGetX(XMVector2Dot(W, vertical)) <= 0.0f)
		{
			isHit = true;
			LOGFLN("下にいるよ 内積");
			if (_pCollisionInfo)
			{
				_pCollisionInfo->normal = _pCollisionInfo->normal * -1.0f;
				_pCollisionInfo->isHit = true;
			}
			continue;
		}*/

		{
			const Vector2 AC = W;
			const Vector2 D = V;

			float signedDistance{ (AC.x * D.y - AC.y * D.x) / XMVectorGetX(XMVector2Length(D)) };
			if (signedDistance > 0.0f)  // 線分の下に居る
			{
				const float MOVE_DELTA{ RADIUS - signedDistance };

				const Vector2 NORM_2D{ XMVector2Normalize(Vector2{ -D.y, D.x }) };
				isHit = true;

				// 当たり判定情報があるなら返す
				if (_pCollisionInfo)
				{
					_pCollisionInfo->normal = { 0.0f, NORM_2D.y, NORM_2D.x };
					_pCollisionInfo->depth = MOVE_DELTA;
					_pCollisionInfo->isHit = true;
				}

				continue;
			}
		}
	}

	return isHit;
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
