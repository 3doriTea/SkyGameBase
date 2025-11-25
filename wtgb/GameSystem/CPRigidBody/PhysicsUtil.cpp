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

bool wtgb::PhysicsUtil::IsHitFromSection(ColliderSet* _pSelfSection, ColliderSet* _pOther)
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
	case Collider::Type::Section:
		wassert(false && "セクション同士の当たり判定はできません。");
		break;
	default:
		break;
	}

	return false;
}

bool wtgb::PhysicsUtil::IsHitFromSphere(ColliderSet* _pSelfSphere, ColliderSet* _pOther)
{
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
		return IsHitFromSection(_pOther, _pSelfSphere);
	case Collider::Type::Sphere:
		Vector3 selfCenterWorld{ XMVector3TransformCoord(_pSelfSphere->pCollider->sphere.center, _pSelfSphere->pTransform->GetWorldMatrix()) };
		Vector3 otherCenterWorld{ XMVector3TransformCoord(_pOther->pCollider->sphere.center, _pOther->pTransform->GetWorldMatrix()) };
		
		// 距離
		float distanceSq{ XMVector3LengthSq(selfCenterWorld - otherCenterWorld).m128_f32[0] };
		// 当たっている閾値
		float threshold{ _pSelfSphere->pCollider->sphere.radius + _pOther->pCollider->sphere.radius };
		float thresholdSq{ threshold * threshold };

		// 二乗同士で判定
		if (distanceSq <= thresholdSq)
		{
			// 当たっている
			return true;
		}
		break;
	default:
		break;
	}

	return false;
}

wtgb::Vector3 wtgb::PhysicsUtil::GetPush(ColliderSet* _pSelf, ColliderSet* _pOther)
{
	return Vector3();
}
