#pragma once
#include "CommonGameComponent.h"
#include "GameSystem/CPRigidBody.h"

namespace wtgb
{
	class CPRigidBody; class RigidBody : public Component<CPRigidBody>
	{
		friend class CPRigidBody;
	public:
		class SETTER(RigidBody)
		{
			SETTER_HEAD(RigidBody)

			SETTER_PARAM(Vector3, velocity)
		};

	public:
		RigidBody() {}
		~RigidBody() {}

		/// <summary>
		/// ‰Šú‰»ˆ—
		/// </summary>
		void Init(ViewerCached _system) override {}
		/// <summary>
		/// XVˆ—
		/// </summary>
		void Update(ViewerCached _system) override {}

	private:
		Vector3 velocity_;
		bool useSphereCollider_;  // ‹…‚Ì“–‚½‚è”»’è‚ğg‚¤‚©
	};
}
