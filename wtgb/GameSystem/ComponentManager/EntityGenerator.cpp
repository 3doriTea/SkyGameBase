#include "pch\pch.h"
#include "EntityGenerator.h"
//#include "GameSystem/Debug.h"

wtgb::EntityGenerator::EntityGenerator() :
	//nextIndex_{ 0 },
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
	EntityId entityId{ wtgb::INVALIED_ID };


	// TODO: アルゴリズム改善が必要
	for (uint32_t i = 0; i < UINT32_MAX; i++)
	{
		if (!useFlag_[i])
		{
			entityId.index = i;
			entityId.version = versions_[i];

			useFlag_[i] = true;
			LOGF("\nEID:{} v:{}, i:{}\n", entityId.id, entityId.version, entityId.index);
			return entityId;
		}
	}


	return entityId;
}

void wtgb::EntityGenerator::Remove(const EntityId _entityId)
{
	RemoveAt(_entityId.index);
}

void wtgb::EntityGenerator::RemoveAt(const uint32_t _index)
{
	// 使っていた場所を掃除
	versions_[_index]++;    // バージョンを上げる
	useFlag_[_index] = false;  // 空家にする
}

const bool wtgb::EntityGenerator::IsInvalidId(const EntityId _checkId) const
{
	// エンティティキャパシティ以上の値なら無効
	if (_checkId.index >= ENTITY_CAPACITY)
	{
		return true;
	}

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

void wtgb::EntityGenerator::RemoveAll()
{
	for (size_t i = 0; i < ENTITY_CAPACITY; i++)
	{
		if (useFlag_[i])
		{
			useFlag_[i] = false;
			versions_[i]++;
		}
	}
}
