#pragma once
#include "CommonGameComponent.h"
#include "GameSystem/CPCollider.h"

namespace wtgb
{
	class COMPONENT(Collider)
	{
		friend class CPCollider;
	public:
		/// <summary>
		/// “–‚½‚è”»’èŒ`ó‚Ìí—Ş
		/// </summary>
		enum struct Type
		{
			Sphere,   // ‹…
			//AABB,   // 
			Section,  // ’f–Ê
		};

		class SETTER(Collider)
		{
			SETTER_HEAD(Collider)

			SETTER_PARAM(Type, colliderType)
		};

	public:
		Collider();
		Collider(Collider& _other);
		~Collider() {}

	private:
		Type colliderType_;
		union
		{
			struct
			{
				float radius;    // ‹…‚Ì”¼Œa
				Vector3 center;  // ‹…‚Ì’†S
			} sphere;
			struct
			{
				std::vector<Vector2> points2D;  // ’f–Êxy’¸“_
			} section;
		};
	};
}
