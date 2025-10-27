#include "pch\pch.h"
#include "EntityGenerator.h"

wtgb::EntityGenerator::EntityGenerator() :
	nextIndex_{ 0 },
	// NOTE: 無効なEntityIdにならないように最初のバージョンは1
	versions_(ENTITY_CAPACITY, 1),
	useFlag_{}
{
}

wtgb::EntityGenerator::~EntityGenerator()
{
}

wtgb::EntityId wtgb::EntityGenerator::Generate()
{
	EntityId newEntityId{ wtgb::INVALIED_ID };

	// TODO: アルゴリズム改善が必要
	for (uint32_t i = 0; i < UINT32_MAX; i++)
	{
		if (!useFlag_[i])
		{
			newEntityId.index = i;
			newEntityId.version = versions_[i];

			useFlag_[i] = true;
			return newEntityId;
		}
	}

	return newEntityId;
}

void wtgb::EntityGenerator::Remove(const EntityId _entityId)
{
	// 使っていた場所を掃除
	versions_[_entityId.index]++;  // バージョンを上げる
	useFlag_[_entityId.id] = false;  // 空家にする
}

const bool wtgb::EntityGenerator::IsInvalidId(const EntityId _checkId) const
{
	// 現在使われていないエンティティなら無効
	if (!useFlag_[_checkId.index])
	{
		return true;
	}

	// バージョンが不一致なら無効
	if (versions_[_checkId.index] != _checkId.version)
	{
		return true;
	}

	return false;
}
