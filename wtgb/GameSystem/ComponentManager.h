#pragma once
#include "pch/pch.h"
#include "Core/Entity.h"
#include "IComponentPool.h"
#include "Utility/Accessor.h"
#include "Core/IGameSystem.h"

namespace wtgb
{
	/// <summary>
	/// コンポーネントプールを管理するクラス
	/// </summary>
	class ComponentManager : public IGameSystem
	{
	public:
		/// <summary>
		/// コンポーネントプールを登録するためだけのアクセッサ
		/// </summary>
		class ComponentPoolRegister : public Accessor<ComponentManager>
		{
		public:
			using Accessor::Accessor;
			~ComponentPoolRegister() {}

			template<typename T>
			void Register();
		};

	public:
		ComponentManager();
		~ComponentManager();

		/// <summary>
		/// 呼び出しタイミングの取得
		/// </summary>
		/// <returns>呼び出しタイミング</returns>
		const CallType GetCallType() override { return CallType::Frame; }

		/// <summary>
		/// 初期化処理
		/// </summary>
		/// <param name="_viewer"></param>
		/// <returns>結果</returns>
		Result Init(const ViewerInit& _viewer) override;
		/// <summary>
		/// 更新処理
		/// </summary>
		/// <param name="_system"></param>
		void Update(const ViewerUpdate& _system) override;
		/// <summary>
		/// 終了処理
		/// </summary>
		void End() override;

		void ReleaseAll();

		void UpdateAll();

		template<typename T>
		void Release(const EntityId _entityId);

		template<typename T>
		T& Get(const EntityId _entityId);

		template<typename T>
		const T& Get(const EntityId _entityId) const;

	private:
		std::vector<IComponentPool*> pools_;  // コンポーネントプールの順番を持っておく
		std::map<std::type_index, IComponentPool*> typeToPools_;  // コンポーネントプールの型変換用
	};
}

template<typename T>
inline void wtgb::ComponentManager::Release(const EntityId _entityId)
{
}

template<typename T>
inline void wtgb::ComponentManager::ComponentPoolRegister::Register()
{
	T* pComponent{ new T{} };
	GetAccess()->pools_.push_back(dynamic_cast<IComponentPool*>(pComponent));
	GetAccess()->typeToPools_.emplace(typeid(T), pComponent);
}


template<typename T>
T& wtgb::ComponentManager::Get(const EntityId _entityId)
{
	T* pComponent{ dynamic_cast<T*>(typeToPools_.at(typeid(T))) };
	assert(pComponent && "指定したコンポーネントが見つからなかった");

	return *pComponent;
}

template<typename T>
inline const T& wtgb::ComponentManager::Get(const EntityId _entityId) const
{
	const T* pComponent{ dynamic_cast<const T*>(typeToPools_.at(typeid(T))) };
	assert(pComponent && "指定したコンポーネントが見つからなかった");

	return *pComponent;
}
