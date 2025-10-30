#pragma once
#include "pch/pch.h"
#include "Core/Entity.h"
#include "Core/IGameSystem.h"
#include "IComponentPool.h"
#include "Core/EntityCapacity.h"

namespace wtgb
{
	/// <summary>
	/// コンポーネントプールの基底クラス
	/// </summary>
	/// <typeparam name="ComponentT">コンポーネント型</typeparam>
	template<typename ComponentT>
	class ComponentPool : public IGameSystem, public IComponentPool
	{
		friend ComponentT;
		//using Pool = std::array<ComponentT, wtgb::ENTITY_CAPACITY>;
		using Pool = std::vector<ComponentT>;

	protected:
		ComponentPool() : system_{ nullptr }, pool_{} {}
		virtual ~ComponentPool() {}

		/// <summary>
		/// 呼び出しタイミングの種類を取得
		/// </summary>
		/// <returns>呼び出しタイミングの種類</returns>
		const CallType GetCallType() { return CallType::Frame; }

		/// <summary>
		/// 初期化処理
		/// </summary>
		Result Init(const ViewerInit& _viewer) override;
		/// <summary>
		/// 更新処理
		/// </summary>
		void Update(const ViewerUpdate& _system) override;
	
	public:
		/// <summary>
		/// 終了処理
		/// </summary>
		virtual void End() override {}

		template<typename T = ComponentT, typename ...Args>
		ComponentT& Add(const EntityId _entityId, const Args& ...args);

		/// <summary>
		/// <para>コンポーネントを取得する</para>
		/// <para>NOTE: 返されたポインタを保存しないでください！</para>
		/// </summary>
		/// <param name="_entityId">エンティティId</param>
		/// <returns>コンポーネントのポインタ / なければ nullptr</returns>
		ComponentT* Get(const EntityId _entityId);

		/// <summary>
		/// エンティティのコンポーネントをはずす
		/// </summary>
		/// <param name="_entityId">外すエンティティId</param>
		void Remove(const EntityId _entityId);

	protected:
		/// <summary>
		/// 初期化処理
		/// </summary>
		virtual void Init() = 0;
		/// <summary>
		/// 更新処理
		/// </summary>
		virtual void Update() = 0;

		ViewerCached& System() { return system_; }

	protected:
		Pool::iterator begin() { return pool_.begin(); }
		Pool::iterator end() { return pool_.end(); }
		Pool::const_iterator begin() const { return pool_.begin(); }
		Pool::const_iterator end() const { return pool_.end(); }

		ComponentT& at(const size_t _index) { return pool_.at(_index); }
		const ComponentT& at(const size_t _index) const { return pool_.at(_index); }

	private:
		bool IsInvalidEntity(const EntityId _entityId);

	private:
		Pool pool_;
		std::bitset<ENTITY_CAPACITY> useFlag_;  // エンティティがコンポーネントを使用しているかフラグ
		ViewerCached system_;
	};
}

#include "ComponentPool.inl"
