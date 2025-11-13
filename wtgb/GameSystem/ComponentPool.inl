#include "ComponentPool.h"
#include "ComponentManager.h"

template<typename ComponentT>
wtgb::Result wtgb::ComponentPool<ComponentT>::Init(const ViewerInit& _viewer)
{
	pool_.resize(wtgb::ENTITY_CAPACITY);

	system_ = _viewer.GetCache();

	Init();
	return Result::Code::Ok;
}


template<typename ComponentT>
void wtgb::ComponentPool<ComponentT>::Update(const ViewerUpdate& _system)
{
	Update();
}

template<typename ComponentT>
inline ComponentT* wtgb::ComponentPool<ComponentT>::Get(const EntityId _entityId)
{
	// 無効なEntityId なら取得しない
	if (IsInvalidEntity(_entityId))
	{
		useFlag_[_entityId.index] = false;
		return nullptr;
	}

	if (useFlag_[_entityId.index])
	{
		return &pool_[_entityId.index];
	}
	else
	{
		return nullptr;
	}
}

template<typename ComponentT>
inline void wtgb::ComponentPool<ComponentT>::Remove(const EntityId _entityId)
{
	// 使わないからフラグ降ろすだけ
	useFlag_[_entityId.index] = false;
}

template<typename ComponentT>
inline void wtgb::ComponentPool<ComponentT>::Clear()
{
	ForEach([](ComponentT& component)
		{
			// 終了処理呼び出していく
			if constexpr (std::is_pointer_v<ComponentT>)
			{
				component->End();
			}
			else
			{
				component.End();
			}
		});

	useFlag_.reset();
}

template<typename ComponentT>
inline void wtgb::ComponentPool<ComponentT>::ForEach(const std::function<void(ComponentT&)>& _callback)
{
	for (size_t i = 0; i < ENTITY_CAPACITY; i++)
	{
		if (useFlag_[i])
		{
			_callback(pool_.at(i));
		}
	}
}

template<typename ComponentT>
inline void wtgb::ComponentPool<ComponentT>::ForEach(const std::function<void(ComponentT&, const size_t)>& _callback)
{
	for (size_t i = 0; i < ENTITY_CAPACITY; i++)
	{
		if (useFlag_[i])
		{
			_callback(pool_.at(i), i);
		}
	}
}

template<typename ComponentT>
inline void wtgb::ComponentPool<ComponentT>::ForEach(const std::function<void(const ComponentT&)>& _callback) const
{
	for (size_t i = 0; i < ENTITY_CAPACITY; i++)
	{
		if (useFlag_[i])
		{
			_callback(pool_.at(i));
		}
	}
}

template<typename ComponentT>
inline void wtgb::ComponentPool<ComponentT>::ForEach(const std::function<void(const ComponentT&, const size_t)>& _callback) const
{
	for (size_t i = 0; i < ENTITY_CAPACITY; i++)
	{
		if (useFlag_[i])
		{
			_callback(pool_.at(i), i);
		}
	}
}

template<typename ComponentT>
inline wtgb::ComponentPool<ComponentT>::Pool::iterator wtgb::ComponentPool<ComponentT>::GetUsedBeginItr()
{
	// 使われているコンポーネントまで走査する
	for (size_t i = 0; i < ENTITY_CAPACITY; i++)
	{
		if (useFlag_[i])
		{
			return pool_.begin() + i;
		}
	}
	
	// 見つからなければ end を返す
	return pool_.end();
}

template<typename ComponentT>
inline wtgb::ComponentPool<ComponentT>::Pool::const_iterator wtgb::ComponentPool<ComponentT>::GetUsedBeginItr() const
{
	// 使われているコンポーネントまで走査する
	for (size_t i = 0; i < ENTITY_CAPACITY; i++)
	{
		if (useFlag_[i])
		{
			return pool_.begin() + i;
		}
	}

	// 見つからなければ end を返す
	return pool_.end();
}

template<typename ComponentT>
inline bool wtgb::ComponentPool<ComponentT>::IsInvalidEntity(const EntityId _entityId)
{
	return System().Get<ComponentManager>().IsInvalidId(_entityId);
}

template<typename ComponentT>
template<typename T, typename ...Args>
ComponentT& wtgb::ComponentPool<ComponentT>::Add(const EntityId _entityId, const Args& ...args)
{
	pool_[_entityId.index] = T{ args... };
	// 使っているからフラグを立てる
	useFlag_[_entityId.index] = true;
	return pool_[_entityId.index];
}
