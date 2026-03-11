#include "pch\pch.h"
#include "CameraMovePlay.h"
#include "../Player.h"
#include "PlayScene/StageLine.h"
#include <algorithm>

namespace
{
	// プレイヤーまでの距離
	const float TO_PLAYER_DISTANCE{ 30.0f };

	// プレイヤーのドラッグ範囲 (ピクセル)
	const int PLAYER_DRAG_RADIUS_PIX{ 130 };
	// プレイヤーのドラッグ範囲の2以上 (ピクセル)
	const int PLAYER_DRAG_RADIUS_PIX_SQ{ PLAYER_DRAG_RADIUS_PIX * PLAYER_DRAG_RADIUS_PIX };

	// 回転速度
	const float MOVE_ANGLE_DEG{ 3.0f };

	const float ANGLE_MAX_DEG{ 80.0f };
	const float ANGLE_MIN_DEG{ -80.0f };

	const float CAMERA_OFFSET_Y_ON_STAGE_LINE{ 3.0f };  // ステージ地面からのオフセット
}

CameraMovePlay::CameraMovePlay() :
	angleY_{ 0.0f },
	angleX_{ 0.0f },
	isDragging_{ false },
	controlMode_{ ControlMode::MoveView },
	previous_{ Vector2Int::Zero() },
	diffValue_{ Vector2Int::Zero() },
	stageLine_{ INVALID_ENTITY },
	emphasisPrevYOffset_{},
	emphasisBoost_{},
	bounceImpactIntensity_{},
	bounceImpactPlayRatio_{}
{
}

void CameraMovePlay::Start(GameObjectReference _ref)
{
	auto [systemView, entityId]{ _ref };

	GameObject* pStageLineObj{ systemView.Get<CPGameObject>().FindGameObject("StageLine") };
	wassert(pStageLineObj && "ステージラインがシーンに存在しないよ！");
	if (pStageLineObj)
	{
		stageLine_ = pStageLineObj->GetEntityId();
	}
}

void CameraMovePlay::Update(GameObjectReference _ref)
{
	using namespace DirectX;

	auto [systemView, entityId]{ _ref };

	float dt{ systemView.Get<GameTime>().GetDeltaTime() };
	Cursor& cursor{ systemView.Get<Cursor>() };
	GameWindow& gameWindow{ systemView.Get<GameWindow>() };
	const Input::InputGetter& input{ systemView.Get<Input>().Getter() };

	// カメラコントローラのゲームオブジェクトの情報

	Transform* pTransform{ systemView.Get<CPTransform>().Get(entityId) };
	GameObject* pGameObject{ systemView.Get<CPGameObject>().Get(entityId)->get() };
	GameObject* pPlayer{ pGameObject->FindGameObject("Player") };

	// マウスカーソルの制御
	if (input.IsMouseDown(MouseCode::Left)  // マウス左押された
		&& gameWindow.IsActiveMainWindow()  // かつウィンドウが最前面
		&& gameWindow.IsDefaultControled())  // かつゲーム画面の操作
	{
		isDragging_ = true;

		Vector2Int windowSize{ gameWindow.GetMainWindowSize() };
		Vector2Int halfWindowSize{ windowSize / 2 };
		Vector2Int cursorPosition{ cursor.GetPosition() };
		
		Vector2Int offsetPos{ cursorPosition - halfWindowSize };
		int radiusSq{ offsetPos.x * offsetPos.x + offsetPos.y * offsetPos.y };

		if (radiusSq <= PLAYER_DRAG_RADIUS_PIX_SQ)
		{
			controlMode_ = ControlMode::MovePlayer;
			previous_ = cursor.GetPosition();
		}
		else
		{
			controlMode_ = ControlMode::MoveView;
			cursor.SetLock(true, cursor.GetPosition());
			cursor.SetShow(false);
		}
		
	}
	if (input.IsMouseUp(MouseCode::Left))
	{
		if (controlMode_ == ControlMode::MoveView)
		{
			cursor.SetCenterLock(false);
			cursor.SetShow(true);
		}
		else  // プレイヤー操作の状態だったら
		{
			const float MOVE_MAX_SPEED{ 10.0f };
			const float CURSOR_MOVE_TO_VELOCITY{ 0.1f };

			Player* pp{ dynamic_cast<Player*>(pPlayer) };

			// マウスの移動量から速度を求める
			Vector3 velocity
			{
				Vector3{ static_cast<float>(diffValue_.x), 0.0f, -static_cast<float>(diffValue_.y) }
				* CURSOR_MOVE_TO_VELOCITY
			};


			// プレイヤーのローカル方向へ変換
			velocity = XMVector3TransformCoord(velocity, XMMatrixRotationY(angleY_));

			pp->AddMove(velocity);

			diffValue_ = Vector2Int::Zero();
		}
		isDragging_ = false;
	}

	// MEMO: angleX_ に加算するとカメラの操作と同期してわからなくなった

	// 目標地点
	Vector3 toPosition{};
	const Vector3 OFFSET{ 0.0f, 0.0f, -TO_PLAYER_DISTANCE };
	Matrix4x4 rotationMatrix{ XMMatrixRotationX(angleX_) * XMMatrixRotationY(angleY_) };
	toPosition = XMVector3TransformCoord(OFFSET, rotationMatrix) + pPlayer->Transform().GetPositionWorld();

#pragma region y軸速度の分迫力をもたせる
	RigidBody& rb{ pPlayer->GetComponent<RigidBody>() };
	float emphasisCurrYOffset{ std::clamp(rb.GetVelocity().y, -10.0f, 10.0f) };

	emphasisBoost_ -= dt * emphasis_.boostDecayRatePerSec;
	if (emphasisBoost_ <= 0.0f)
	{
		emphasisBoost_ = 0.0f;
	}

	// 下がって(-) から 上がる (+)
	if (emphasisPrevYOffset_ - emphasisCurrYOffset < emphasis_.boostThreshold)
	{
		// 衝撃を加える
		emphasisBoost_ = emphasis_.boostValue;

		// バウンドの衝撃も加える
		bounceImpactPlayRatio_ = { 0.3f, 0.8f, 0.0f };
		bounceImpactIntensity_ = bounceImpact.startIntensity;
	}

	// MEMO: expfの中の -が抜けると無限大に発散するよ()
	float t = 1.0f - std::expf(-(emphasis_.responseRatio + emphasisBoost_) * dt);
	emphasisPrevYOffset_ = Mathf::Lerp(emphasisPrevYOffset_, emphasisCurrYOffset, t);
	toPosition.y -= emphasisPrevYOffset_;
#pragma endregion

#pragma region バウンド中の衝撃
	// カメラを揺らす
	toPosition = toPosition + Vector3
	{
		std::sinf(bounceImpactPlayRatio_.x) * bounceImpactIntensity_.x,
		std::sinf(bounceImpactPlayRatio_.y) * bounceImpactIntensity_.y,
		std::sinf(bounceImpactPlayRatio_.z) * bounceImpactIntensity_.z,
	};

	// 再生レートを進める
	bounceImpactPlayRatio_ = bounceImpactPlayRatio_ + bounceImpact.frequencyPerSec * dt;
	bounceImpactPlayRatio_.x = std::fmodf(bounceImpactPlayRatio_.x, 1.0f);
	bounceImpactPlayRatio_.y = std::fmodf(bounceImpactPlayRatio_.y, 1.0f);
	bounceImpactPlayRatio_.z = std::fmodf(bounceImpactPlayRatio_.z, 1.0f);

	// 揺れの強さを減衰させる
	float dampingT = 1.0f - std::expf(-(bounceImpact.dampingRatioPerSec) * dt);
	bounceImpactIntensity_ = Mathf::Lerp(
		bounceImpactIntensity_,
		Vector3::Zero(),
		dampingT);
#pragma endregion


	pTransform->SetPositionWorld(toPosition);

	{  // プレイヤーが前に進んでいるとき、カメラをだんだんと前に向ける処理
		
		if (rb.GetVelocity().z > 0.0f)
		{
			Vector3 rotation{ pTransform->GetRotation() };
			rotation.y /= 1.01f;
			pTransform->SetRotation(rotation);
		}
	}
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
	}// うまく行っているほどチャネルが増える　他のバッグの音が増えることで感情が高ぶる
// 失敗すると減っていく

	if (stageLine_ != INVALID_ENTITY)
	{
		GameObject* pStageLineObj{ systemView.Get<CPGameObject>().FindGameObject(stageLine_) };
		StageLine* pStageLine{ dynamic_cast<StageLine*>(pStageLineObj) };

		wassert(pStageLine && "誤ったステージラインのエンティティIdが取得されている！");

		if (pStageLine)
		{
			Vector3 cameraWorldPos{ pTransform->GetPosition() };
			float posY{ pStageLine->GetPosY(cameraWorldPos) };
			posY = posY + CAMERA_OFFSET_Y_ON_STAGE_LINE;  // オフセット分上げてあげる

			// カメラが地面に埋まっているなら上げる
			if (cameraWorldPos.y <= posY)
			{
				Vector3 a{ toPlayerDir };
				Vector2 b{ cameraWorldPos.x, cameraWorldPos.y };

				float ratio{ XMVectorGetX(XMVector3Cross(toPlayerDiff, b)) / XMVectorGetX(XMVector3Cross(a, b)) };

				cameraWorldPos.y = posY;


				pTransform->SetPosition(cameraWorldPos);
			}
		}
	}

	// ドラッグ中の処理
	Vector2Int move{ cursor.GetFrameMove() };
	if (isDragging_)
	{
		switch (controlMode_)
		{
		case CameraMovePlay::ControlMode::MoveView:
		{
			float addY{ static_cast<float>(move.y) * dt * (XMConvertToRadians(MOVE_ANGLE_DEG)) };
			angleX_ += addY;

			float addX{ static_cast<float>(move.x) * dt * (XMConvertToRadians(MOVE_ANGLE_DEG)) };
			angleY_ += addX;
			break;
		}
		case CameraMovePlay::ControlMode::MovePlayer:
		{
			Vector2Int current{ cursor.GetPosition() };
			diffValue_ += current - previous_;
			previous_ = current;
			break;
		}
		default:
			break;
		}
	}
}

void CameraMovePlay::End(GameObjectReference _ref)
{
}
