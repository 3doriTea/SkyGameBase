#pragma once
#include "Core/IGameSystem.h"

namespace wtgb
{
	/// <summary>
	/// カメラシステム
	/// </summary>
	class Camera : public IGameSystem
	{
	public:
		Camera();
		~Camera();

		/// <summary>
		/// 更新タイミングを取得する
		/// </summary>
		/// <returns>更新のタイミング</returns>
		const CallType GetCallType() override { return CallType::Frame; }

		/// <summary>
		/// 初期化処理
		/// </summary>
		/// <param name="_viewer">システムのビュア</param>
		/// <returns>結果</returns>
		Result Init(const ViewerInit& _viewer) override;
		/// <summary>
		/// 更新処理
		/// </summary>
		/// <param name="_system">システムのビュア</param>
		void Update(const ViewerUpdate& _system) override;
		/// <summary>
		/// 終了処理
		/// </summary>
		void End() override;

		/// <summary>
		/// プロジェクション行列を取得
		/// </summary>
		/// <returns>4x4行列</returns>
		Matrix4x4 GetProjectionMatrix() const;
		/// <summary>
		/// ビュー行列を取得
		/// </summary>
		/// <returns>4x4行列</returns>
		Matrix4x4 GetViewMatrix() const;

		/// <summary>
		/// カメラが向いているベクトルを取得する
		/// </summary>
		/// <returns>正規化されていないベクトル</returns>
		Vector3 GetDisplacement() const { return targetPosition_ - position_; }
		/// <summary>
		/// カメラが向いている方向ベクトル
		/// </summary>
		/// <returns>正規化された方向ベクトル</returns>
		Vector3 GetDirection() const { return DirectX::XMVector3Normalize(GetDisplacement()); }
		Vector3 GetPosition() const { return position_; }
	public:
		Vector3 position_;        // 位置座標
		Vector3 targetPosition_;  // 焦点座標
	private:
		Matrix4x4 viewMatrix_;        // ビュー行列
		Matrix4x4 projectionMatrix_;  // プロジェクション行列

	};
}
