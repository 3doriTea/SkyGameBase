#pragma once
#include "pch/pch.h"
#include "Core/Entity.h"
#include "Core/IGameSystem.h"

namespace wtgb
{
	template<typename ComponentT>
	class ComponentPool : public IGameSystem
	{
		using Pool = std::array<ComponentT, CAPACITY_SIZE>;
		using Versions = std::vector<uint32_t, CAPACITY_SIZE>;
	public:
		ComponentPool() {}
		virtual ~ComponentPool() {}

		/// <summary>
		/// 呼び出しタイミングの種類を取得
		/// </summary>
		/// <returns>呼び出しタイミングの種類</returns>
		const CallType GetCallType() { return CallType::Frame; }

		/// <summary>
		/// 初期化処理
		/// </summary>
		void Result Init(const ViewerInit& _viewer) override;
		/// <summary>
		/// 更新処理
		/// </summary>
		void Update(const ViewerUpdate& _system) override;
		/// <summary>
		/// 終了処理
		/// </summary>
		void End() override;

	protected:
		Pool::iterator begin() { pool_.begin(); }
		Pool::iterator end() { pool_.end(); }
		Pool::const_iterator begin() const { pool_.begin(); }
		Pool::const_iterator end() const { pool_.end(); }

	private:
		Pool pool_;
	};
}

#include "ComponentPool.inl"
