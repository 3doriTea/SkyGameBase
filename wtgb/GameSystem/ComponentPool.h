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
		//using Pool = std::array<ComponentT, wtgb::ENTITY_CAPACITY>;
		using Pool = std::vector<ComponentT>;
	public:
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
		/// <summary>
		/// 終了処理
		/// </summary>
		virtual void End() override {}

		template<typename T = ComponentT, typename ...Args>
		ComponentT& Add(const EntityId _entityId, const Args& ...args);

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

		ComponentT& at(const size_type _index) { return pool_.at(); }
		const ComponentT& at(const size_type _Pos) const { return pool_.at(); }

	private:
		Pool pool_;
		ViewerCached system_;
	};
}

#include "ComponentPool.inl"
