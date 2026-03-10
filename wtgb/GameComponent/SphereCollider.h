//#pragma once
//#include "CommonGameComponent.h"
//#include "GameSystem/CPRigidBody.h"
//
//namespace wtgb
//{
//	class CPRigidBody; class RigidBody : public Component<CPRigidBody>
//	{
//		friend class CPRigidBody;
//	public:
//		class SETTER(RigidBody)
//		{
//			SETTER_HEAD(RigidBody)
//
//			SETTER_PARAM(Vector3, offset)
//			SETTER_PARAM(float, radius)
//		};
//
//	public:
//		RigidBody() {}
//		~RigidBody() {}
//
//		/// <summary>
//		/// 初期化処理
//		/// </summary>
//		void Init(ViewerCached _system) override {}
//		/// <summary>
//		/// 更新処理
//		/// </summary>
//		void Update(ViewerCached _system) override {}
//
//	private:
//		Vector3 offset_;
//		float radius_;
//	};
//}
