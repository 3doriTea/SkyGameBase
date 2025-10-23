#pragma once
#include "Core/IComponent.h"

namespace wtgb
{
	class Transform;
	class Transform::Setter;

	class Transform : public IComponent<Transform::Setter>
	{
	public:
		class Setter : public GameObjectBuilder::Setter<Transform>
		{
		public:
			using GameObjectBuilder::Setter<Transform>::Setter;
			~Setter() {}

			Setter& Position(const Vector3& _position) { GetAccess()->position_ = _position; return *this; }
			Setter& Rotation(const Vector3& _rotation) { GetAccess()->rotation_ = _rotation; return *this; }
			Setter& Scale(const Vector3& _scale)       { GetAccess()->scale_ = _scale;       return *this; }
		};

	public:
		Transform();
		~Transform();

	private:
		Vector3 position_;  // À•W
		Vector3 rotation_;  // ‰ñ“]
		Vector3 scale_;	    // ‘å‚«‚³

		Matrix4x4 translateMatrix_;  // ˆÚ“®s—ñ
		Matrix4x4 rotateMatrix_;     // ‰ñ“]s—ñ
		Matrix4x4 scaleMatrix_;      // Šgks—ñ
	};
}
