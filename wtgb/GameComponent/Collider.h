#pragma once
#include <cassert>
#include "CommonGameComponent.h"
#include "GameSystem/CPCollider.h"

namespace
{
	/// <summary>
	/// コライダータグの数
	/// </summary>
	const size_t TAG_COUNT{ sizeof(uint32_t) * 8 };
}

namespace wtgb
{
	class COMPONENT(Collider)
	{
		friend class CPCollider;
		friend class CPRigidBody;
		friend class PhysicsUtil;
	public:
		/// <summary>
		/// 当たり判定形状の種類
		/// </summary>
		enum struct Type
		{
			Sphere,   // 球
			//AABB,   // 
			Section,  // 断面
		};

		class SETTER(Collider)
		{
			SETTER_HEAD(Collider)

			SETTER_PARAM(Type, colliderType)
			SETTER_PARAM(uint32_t, tag)
		};

	public:
		Collider();
		Collider(const Collider& _other);
		~Collider() {}

		inline Collider& operator=(const Collider& _other)
		{
			colliderType_ = _other.colliderType_;
			switch (_other.colliderType_)
			{
			case Type::Section:
				section = _other.section;
				break;
			case Type::Sphere:
				sphere = _other.sphere;
				break;
			default:
				assert(false && "未実装の当たり判定タイプ");
				break;
			}

			return *this;
		}

		/// <summary>
		/// 当たり判定の形状種類を取得する
		/// </summary>
		/// <returns>当たり判定の形状種類</returns>
		Type GetColliderType() const { return colliderType_; }

		/// <summary>
		/// 2Dでの断面xy頂点をセットする
		/// </summary>
		/// <param name="_src">ソースとなるxy頂点</param>
		void SetPoints2D(const std::vector<Vector2>& _src);

		void SetRadius(const float _radius) { sphere.radius = _radius; }

		/// <summary>
		/// タグフラグ全体をセットする
		/// </summary>
		/// <param name="_flags">フラグ値</param>
		void SetTagFlag(const uint32_t _flags) { tag_ = _flags; }

		/// <summary>
		/// １つのタグフラグをセットする
		/// </summary>
		/// <param name="_index">フラグのインデクス(enum : uint32_tにして使用)</param>
		/// <param name="_flag">立っている true / false</param>
		void SetTag(const size_t _index, const bool _flag) { tag_.set(_index, _flag); }

		/// <summary>
		/// 指定したタグが付いているかチェックする
		/// </summary>
		/// <param name="_index">フラグのインデクス(enum : uint32_tにして使用)</param>
		/// <returns>タグを持っている true / false</returns>
		bool HasTag(const size_t _index) const { return tag_.test(_index); }

	private:
		Type colliderType_;
		//union
		//{
			struct
			{
				float radius;    // 球の半径
				Vector3 center;  // 球の中心
			} sphere;
			struct
			{
				std::vector<Vector2> points2D;  // 断面xy頂点
			} section;
		//};
		std::bitset<TAG_COUNT> tag_;
	};
}
