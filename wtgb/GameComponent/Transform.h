#pragma once
#include "CommonGameComponent.h"
#include "GameSystem/CPTransform.h"

namespace wtgb
{
	class COMPONENT(Transform)
	{
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

		void Update() override {}

	private:
		Vector3 position_;  // À•W
		Vector3 rotation_;  // ‰ñ“]
		Vector3 scale_;     // ‘å‚«‚³

		Matrix4x4 translateMatrix_;  // ˆÚ“®s—ñ
		Matrix4x4 rotateMatrix_;     // ‰ñ“]s—ñ
		Matrix4x4 scaleMatrix_;      // Šgks—ñ
	};
}
