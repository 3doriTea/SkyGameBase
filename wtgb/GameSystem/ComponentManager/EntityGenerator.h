#pragma once
#include "pch/pch.h"
#include "Core/EntityCapacity.h"
#include "Core/Entity.h"

namespace wtgb
{
	/// <summary>
	/// エンティティの生成をする
	/// </summary>
	class EntityGenerator
	{
	public:
		EntityGenerator();
		~EntityGenerator();

		/// <summary>
		/// 新規エンティティを生成する
		/// </summary>
		/// <returns>新規エンティティのId</returns>
		EntityId Generate();

		/// <summary>
		/// エンティティを除去する
		/// </summary>
		/// <param name="_entityId">無効となるエンティティId</param>
		void Remove(const EntityId _entityId);

		/// <summary>
		/// 無効なエンティティIdか確認する
		/// </summary>
		/// <param name="_checkId">確認するエンティティId</param>
		/// <returns>無効である true / false</returns>
		const bool IsInvalidId(const EntityId _checkId) const;

		/// <summary>
		/// すべてのエンティティを除去する
		/// </summary>
		void RemoveAll();

	private:
		//const bool IsEmpty(const EntityId)

	private:
		//uint32_t nextIndex_;  // 次生成するときのエンティティId
		std::vector<uint32_t> versions_;  // エンティティの最新バージョン
		std::bitset<ENTITY_CAPACITY> useFlag_;  // エンティティが存在しているかのフラグ
	};
}
