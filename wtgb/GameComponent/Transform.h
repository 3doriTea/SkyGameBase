#pragma once
#include "CommonGameComponent.h"
#include "GameSystem/CPTransform.h"

namespace wtgb
{
	class COMPONENT(Transform)
	{
		friend CPTransform;
	public:
		class SETTER(Transform)
		{
			SETTER_HEAD(Transform)

			SETTER_PARAM(Vector3, position)
			SETTER_PARAM(Vector3, rotation)
			SETTER_PARAM(Vector3, scale)
		};

	public:
		Transform() {}
		~Transform() {}

		void Init(ViewerCached system_) override {}
		void Update(ViewerCached system_) override {}

		void SetPosition(const Vector3& _position) { position_ = _position; }
		void SetRotation(const Vector3& _rotation) { rotation_ = _rotation; }
		void SetScale(const Vector3& _scale)       { scale_ = _scale; }
		Vector3 GetPosition() const                { return position_; }
		Vector3 GetRotation() const                { return rotation_; }
		Vector3 GetScale() const                   { return scale_; }

		Matrix4x4 GetWorldMatrix() const { return worldMatrix_; }
		Matrix4x4 GetNormalMatrix() const { return rotateMatrix_; }

	private:
		Vector3 position_;  // 座標
		Vector3 rotation_;  // 回転
		Vector3 scale_;     // 大きさ

		Matrix4x4 translateMatrix_;  // 移動行列
		Matrix4x4 rotateMatrix_;     // 回転行列
		Matrix4x4 scaleMatrix_;      // 拡縮行列

		Matrix4x4 localMatrix_;      // ローカル行列
		Matrix4x4 worldMatrix_;      // ワールド行列
	};
}
