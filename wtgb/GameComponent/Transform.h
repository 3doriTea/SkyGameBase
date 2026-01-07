#pragma once
#include "Helper/CommonGameComponent.h"

namespace wtgb
{
	class COMPONENT(Transform)
	{
		friend class CPTransform;

		COMPONENT_HEAD(Transform)
	public:
		class SETTER(Transform)
		{
			SETTER_HEAD(Transform)

			SETTER_PARAM(Vector3, position)
			SETTER_PARAM(Vector3, rotation)
			SETTER_PARAM(Vector3, scale)
		};

	public:
		Transform();
		~Transform() {}

		/// <summary>
		/// 初期化処理
		/// </summary>
		void Init(ViewerCached _system) override {}
		/// <summary>
		/// 更新処理
		/// </summary>
		void Update(ViewerCached _system) override {}

		/// <summary>
		/// ローカル座標をセットする
		/// </summary>
		inline void SetPosition(const Vector3& _position) { position_ = _position; }
		/// <summary>
		/// ローカル回転角度をセットする
		/// </summary>
		/// <param name="_rotation">ラジアンオイラー角</param>
		inline void SetRotation(const Vector3& _rotation) { rotation_ = _rotation; }
		/// <summary>
		/// ローカルスケールをセットする
		/// </summary>
		/// <param name="_scale">スケール</param>
		inline void SetScale(const Vector3& _scale)       { scale_ = _scale; }
		/// <summary>
		/// ローカル座標を取得する
		/// </summary>
		/// <returns>ローカル座標</returns>
		inline Vector3 GetPosition() const                { return position_; }
		/// <summary>
		/// ローカル回転角度を取得する
		/// </summary>
		/// <returns>ラジアンオイラー角</returns>
		inline Vector3 GetRotation() const                { return rotation_; }
		/// <summary>
		/// ローカルスケールを取得する
		/// </summary>
		/// <returns>スケール</returns>
		inline Vector3 GetScale() const                   { return scale_; }

		/// <summary>
		/// ワールド座標をセットする
		/// </summary>
		/// <param name="_worldPosition">ワールド座標</param>
		void SetPositionWorld(const Vector3& _worldPosition);
		/// <summary>
		/// ワールド座標を取得する
		/// </summary>
		/// <returns>ワールド座標</returns>
		Vector3 GetPositionWorld() const;

		/// <summary>
		/// ワールドラジアンオイラー角をセットする
		/// </summary>
		/// <param name="_worldPosition">ワールドラジアンオイラー角</param>
		void SetRotationWorld(const Vector3& _worldRotation);
		/// <summary>
		/// ワールドラジアンオイラー角を取得する
		/// </summary>
		/// <returns>ワールドラジアンオイラー角</returns>
		Vector3 GetRotationWorld() const;

		/// <summary>
		/// ワールド行列を取得する
		/// </summary>
		/// <returns>ワールド変換行列</returns>
		inline Matrix4x4 GetWorldMatrix() const { return worldMatrix_; }
		/// <summary>
		/// 法線の変換行列 (回転行列) を取得する
		/// </summary>
		/// <returns>法線の変換行列</returns>
		inline Matrix4x4 GetNormalMatrix() const { return worldRotateMatrix_; }

		/// <summary>
		/// ローカル行列を取得する
		/// </summary>
		/// <returns>ローカル変換行列</returns>
		inline Matrix4x4 GetLocalMatrix() const { return localMatrix_; }
#pragma region 方向ベクトルの取得
		inline Vector3 GetForward() const { return Vector3::Forward() *= worldRotateMatrix_; }
#pragma endregion

	private:
		Vector3 position_;  // ローカル座標
		Vector3 rotation_;  // ローカル回転角度 (ラジアンのオイラー角)
		Vector3 scale_;     // ローカルスケール

		Matrix4x4 translateMatrix_;  // 移動行列
		Matrix4x4 rotateMatrix_;     // 回転行列
		Matrix4x4 scaleMatrix_;      // 拡縮行列

		Matrix4x4 localMatrix_;        // ローカル行列
		Matrix4x4 worldMatrix_;        // ワールド行列
		Matrix4x4 worldRotateMatrix_;  // ワールド回転行列
	};
}
