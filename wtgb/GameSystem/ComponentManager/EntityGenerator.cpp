#include "pch\pch.h"
#include "EntityGenerator.h"

wtgb::EntityGenerator::EntityGenerator(const size_t _capacity) :
	nextIndex_{ 0 },
	// NOTE: 無効なEntityIdにならないように最初のバージョンは1
	versions_(_capacity, 1),
	useFlag_{}
{
}

wtgb::EntityGenerator::~EntityGenerator()
{
}

void wtgb::EntityGenerator::Reset()
{
	currentVersion_++;
	assert(currentVersion_ < UINT32_MAX && "バージョンの空きがなくなった");

	nextIndex_ = 0;
}

wtgb::EntityId wtgb::EntityGenerator::Generate()
{
	EntityId newEntityId{};
	
	for (int i = 0; i < nextIndex_; i++)
	{
		if ()
	}
	
	newEntityId.index = nextIndex_;
	newEntityId.version = currentVersion_;

	nextIndex_++;

	return newEntityId;
}

void wtgb::EntityGenerator::Remove(const EntityId _entityId)
{
	
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
