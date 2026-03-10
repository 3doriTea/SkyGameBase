#pragma once
#include <pch/pch.h>

namespace wtgb
{
	/// <summary>
	/// エンティティの識別値
	/// </summary>
	struct EntityId
	{
		union 
		{
			uint64_t id;  // エンティティ識別番号
			struct
			{
				uint32_t version;  // エンティティの所属世界バージョン
				uint32_t index;    // エンティティの配列番号
			};
		};
	};

	inline bool operator==(const EntityId _left, const EntityId _right) { return _left.id == _right.id; }
	inline bool operator!=(const EntityId _left, const EntityId _right) { return !(_left.id == _right.id); }
	inline bool operator<(const EntityId _left, const EntityId _right)  { return _left.id < _right.id; }

	/// <summary>
	/// 無効なエンティティId
	/// </summary>
	static const uint64_t INVALIED_ID{ 0 };
	/// <summary>
	/// 無効なエンティティバージョン
	/// </summary>
	static const uint32_t INVALIED_VERSION{ 0 };
	/// <summary>
	/// 無効なエンティティインデクス
	/// </summary>
	static const uint32_t INVALIED_INDEX{ 0 };
	/// <summary>
	/// 無効なエンティティ
	/// </summary>
	static const EntityId INVALID_ENTITY{ INVALIED_ID };

}
