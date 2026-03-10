#pragma once
#include "pch/pch.h"
#include "Core/Entity.h"
#include "IComponentPool.h"
#include "Utility/Accessor.h"
#include "Core/IGameSystem.h"
#include "ComponentManager/EntityGenerator.h"

namespace wtgb
{
	/// <summary>
	/// コンポーネントプールを管理するクラス
	/// </summary>
	class ComponentManager : public IGameSystem
	{
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

		/// <summary>
		/// エンティティを生成する
		/// </summary>
		/// <returns>新しく生成されたエンティティId</returns>
		EntityId GenerateEntity();
		/// <summary>
		/// 前に生成したエンティティのIdを取得する
		/// </summary>
		/// <returns>前に生成したエンティティのId</returns>
		EntityId GetPrevEntity() const { return prevEntityId_; }

		/// <summary>
		/// エンティティIdが無効か否か
		/// </summary>
		/// <param name="_checkId"></param>
		/// <returns></returns>
		const bool IsInvalidId(const EntityId _checkId) const { return entityGenerator_.IsInvalidId(_checkId); }

		/// <summary>
		/// エンティティを消す
		/// </summary>
		/// <param name="_entityId">消すエンティティId</param>
		void RemoveEntity(const EntityId _entityId);

		template<typename T>
		T& Add(const EntityId _entityId);

		template<typename T>
		T& Get(const EntityId _entityId);

		template<typename T>
		const T& Get(const EntityId _entityId) const;

		/// <summary>
		/// 削除予定のエンティティインデックスを取得する
		/// </summary>
		/// <returns>エンティティインデックス</returns>
		const std::vector<uint32_t>& GetToRemoveEntityIndices() const { return toRemoveEntityIndices_; }

		/// <summary>
		/// 削除予定のエンティティインデックスをリセットする
		/// </summary>
		void ResetToRemoveEntityIndices();

		/// <summary>
		/// 全エンティティを除去する
		/// </summary>
		void RemoveAllEntity();

		/// <summary>
		/// コンポーネントプールの破棄が必要か
		/// </summary>
		/// <returns>必要である true / false</returns>
		const bool NeedsClearComponents() const { return needsClearComponents_; }

		/// <summary>
		/// <para>全コンポーネントの破棄依頼をする</para>
		/// <para>NOTE: 全Updateが終わったあとに処理される → 早めの呼び出しが必要</para>
		/// </summary>
		void ClearComponents() { needsClearComponents_ = true; }

	private:
		std::vector<uint32_t> toRemoveEntityIndices_;  // 削除対象のエンティティId
		std::vector<IComponentPool*> pools_;  // コンポーネントプールの順番を持っておく
		std::map<std::type_index, IComponentPool*> typeToPools_;  // コンポーネントプールの型変換用
		EntityGenerator entityGenerator_;  // エンティティ生成
		ViewerCached system_;    // システムビューアのキャッシュ
		EntityId prevEntityId_;  // 前に生成したエンティティのId
		GameSystemCollection::ComponentPoolAccessor componentPoolAccessor_;
		bool needsClearComponents_;
	};
}

#include "ComponentManager.inl"
