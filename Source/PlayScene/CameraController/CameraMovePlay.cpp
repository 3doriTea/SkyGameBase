#include "pch\pch.h"
#include "CameraMovePlay.h"

void CameraMovePlay::Start()
{
}

void CameraMovePlay::Update(ViewerCached& _system, const EntityId _entityId)
{
	using namespace DirectX;

	float dt{ _system.Get<GameTime>().GetDeltaTime() };
	Camera& camera{ _system.Get<Camera>() };
	Cursor& cursor{ _system.Get<Cursor>() };
	const Input::InputGetter& input{ _system.Get<Input>().Getter() };

	// カメラコントローラのゲームオブジェクトの情報

	Transform* pTransform{ _system.Get<CPTransform>().Get(_entityId) };
	GameObject* pGameObject{ _system.Get<CPGameObject>().Get(_entityId) };

	GameObject* pPlayer{ pGameObject->FindGameObject("Player") };

#if 0
	{  // 振動
		Vector3 forward{ XMVector3Normalize(pPlayer->Transform().GetPositionWorld() - Transform().GetPosition()) };
		Vector3 up{ XMVector3Normalize(Vector3::Up()) };

		Vector3 right{ XMVector3Normalize(XMVector3Cross(up, forward)) };

		Vector3 verticalUp{ XMVector3Cross(forward, right) };

		Matrix4x4 lookMatrix
		{
			right,
			verticalUp,
			forward,
			Vector4{ 0, 0, 0, 1.0f },
		};

		Vector3 rotation{ Transform().GetRotation() };

		//using Quaternion = XMVECTOR;
		/*Quaternion qua{ XMQuaternionRotationRollPitchYawFromVector(rotation) };*/

		rotation = XMVector3TransformCoord(rotation, lookMatrix);
		Transform().SetRotation(rotation);

		LOGFLN("Rot({}, {}, {})", rotation.x, rotation.y, rotation.z);
	}
#endif

	// プレイヤーまでの差分ベクトル
	Vector3 toPlayerDiff{ pPlayer->Transform().GetPositionWorld() - Transform().GetPositionWorld() };
	// プレイヤーを向く方向ベクトル
	Vector3 toPlayerDir{ XMVector3Normalize(toPlayerDiff) };

	{
		// MEMO: あるベクトルからあるベクトルへの回転は必ず2回の操作で完結する
		//     : 2つに垂直な1つの軸ベクトルを見つけ
		//     : その軸で回転させる

		Vector3 forward{ Vector3::Forward() };

		Vector3 direction{ toPlayerDir };

		// 2軸平面に垂直なベクトル = 回転軸となる法線ベクトル
		Vector3 normal{ XMVector3Cross(forward, direction) };

		if (XMVectorGetX(XMVector3Length(normal)) <= FLT_EPSILON)
		{
			return;  // ほぼ0なら法線が無限にあるため計算できない
		}

		float rotationAngle  // 回転角度 (ラジアン)
		{
			XMVectorGetX(XMVector3AngleBetweenVectors(forward, direction))
		};

		Matrix4x4 rotationMatrix{ XMMatrixRotationAxis(normal, rotationAngle) };


		XMFLOAT4X4 m{};
		XMStoreFloat4x4(&m, rotationMatrix);

		Vector3 rotation{ Transform().GetRotation() };

		if (std::abs(m._32) < 0.99999f)
		{
			rotation.x = std::asin(-m._32);
			rotation.y = std::atan2(m._31, m._33);
			rotation.z = std::atan2(m._12, m._22);
		}
		else  // ジンバルロック回避する
		{
			rotation.x = std::copysign(XM_PIDIV2, -m._32);
			rotation.y = std::atan2(-m._13, m._11);
			rotation.z = 0.0f;
		}

		Transform().SetRotation(rotation);
	}

	if (XMVectorGetX(XMVector3Length(toPlayerDiff)) > 30.0f)
	{
		Vector3 position{ Transform().GetPositionWorld() };

		position = position + toPlayerDir;

		Transform().SetPositionWorld(position);
	}

	camera.targetPosition_ = Transform().GetPosition() + Transform().GetForward();
	camera.position_ = Transform().GetPosition();
}

void CameraMovePlay::End()
{
}
