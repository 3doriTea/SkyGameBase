#include "pch\pch.h"
#include "CameraMovePlay.h"

namespace
{
	// プレイヤーまでの距離
	const float TO_PLAYER_DISTANCE{ 30.0f };
}

CameraMovePlay::CameraMovePlay() :
	angleY_{ 0.0f },
	angleX_{ 0.0f },
	isDragging_{ false },
	controlMode_{ ControlMode::MoveView }
{
}

void CameraMovePlay::Start(GameObjectReference _ref)
{
}

void CameraMovePlay::Update(GameObjectReference _ref)
{
	using namespace DirectX;

	auto [systemView, entityId]{ _ref };

	float dt{ systemView.Get<GameTime>().GetDeltaTime() };
	Cursor& cursor{ systemView.Get<Cursor>() };
	const Input::InputGetter& input{ systemView.Get<Input>().Getter() };

	// カメラコントローラのゲームオブジェクトの情報

	Transform* pTransform{ systemView.Get<CPTransform>().Get(entityId) };
	GameObject* pGameObject{ systemView.Get<CPGameObject>().Get(entityId) };
	GameObject* pPlayer{ pGameObject->FindGameObject("Player") };

	// マウスカーソルの制御
	if (input.IsMouseDown(MouseCode::Left))
	{
		cursor.SetCenterLock(true);
		cursor.SetShow(false);
		isDragging_ = true;
		LOGFLN("pos:({}, {})", cursor.GetPosition().x, cursor.GetPosition().y);
	}
	if (input.IsMouseUp(MouseCode::Left))
	{
		cursor.SetCenterLock(false);
		cursor.SetShow(true);
		isDragging_ = false;
	}

	// 目標地点
	Vector3 toPosition{};

	const Vector3 OFFSET{ 0.0f, 0.0f, -TO_PLAYER_DISTANCE };

	Matrix4x4 rotationMatrix{ XMMatrixRotationX(angleX_) * XMMatrixRotationY(angleY_) };
	toPosition = XMVector3TransformCoord(OFFSET, rotationMatrix) + pPlayer->Transform().GetPositionWorld();

	pTransform->SetPositionWorld(toPosition);

	// プレイヤーまでの差分ベクトル
	Vector3 toPlayerDiff{ pPlayer->Transform().GetPositionWorld() - pTransform->GetPositionWorld() };
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

		// ほぼ0なら法線が無限にあるため計算できない
		if (XMVectorGetX(XMVector3Length(normal)) > FLT_EPSILON)
		{
			float rotationAngle  // 回転角度 (ラジアン)
			{
				XMVectorGetX(XMVector3AngleBetweenVectors(forward, direction))
			};

			Matrix4x4 rotationMatrix{ XMMatrixRotationAxis(normal, rotationAngle) };


			XMFLOAT4X4 m{};
			XMStoreFloat4x4(&m, rotationMatrix);

			Vector3 rotation{ pTransform->GetRotation() };

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

			pTransform->SetRotation(rotation);
		}
	}

	Vector2Int move{ cursor.GetFrameMove() };

	// ドラッグ中の処理
	if (isDragging_)
	{
		angleX_ += static_cast<float>(move.y) * ((XM_PI / 180.0f) * 3.0f) * dt;
		angleY_ += static_cast<float>(move.x) * ((XM_PI / 180.0f) * 3.0f) * dt;

		//Vector3 pos{ pTransform->GetPosition() };
		//Vector3 pos{ pTransform->GetPosition() };

		//Vector3 moveLocal{ static_cast<float>(move.x), static_cast<float>(move.y), -TO_PLAYER_DISTANCE };

		//moveLocal = moveLocal * dt;
		
		/*LOGFLN("pos({}, {}, {})", pos.x, pos.y, pos.z);
		LOGFLN("moveLocal({}, {}, {})", moveLocal.x, moveLocal.y, moveLocal.z);*/

		//Vector3 moveWorld{ moveLocal };
		//Vector3 moveWorld{ XMVector3TransformCoord(moveLocal, XMMatrixRotationY(pTransform->GetRotation().y)) };

		//pTransform->SetPosition(pos + moveWorld);


	}
}

void CameraMovePlay::End(GameObjectReference _ref)
{
}
