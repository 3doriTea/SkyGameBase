#pragma once
#include "pch/pch.h"
#include "Core/Entity.h"
#include "Core/IGameSystem.h"
#include "IComponentPool.h"
#include "Core/EntityCapacity.h"
#include "ComponentPool/ComponentPoolIterator.h"

namespace wtgb
{
	/// <summary>
	/// コンポーネントプールの基底クラス
	/// </summary>
	/// <typeparam name="ComponentT">コンポーネント型</typeparam>
	template<typename ComponentT>
	class ComponentPool : public IGameSystem, public IComponentPool
	{
		friend ComponentT;
		//using Pool = std::array<ComponentT, wtgb::ENTITY_CAPACITY>;
		using Pool = std::vector<ComponentT>;
		using UsingFlag = std::bitset<ENTITY_CAPACITY>;

	protected:
		/// <summary>
		/// コンポーネントプールへのイテレータ
		/// </summary>
		class PoolIterator
		{
		public:
			PoolIterator(const Pool& _pool, const std::bitset<ENTITY_CAPACITY>& _used, Pool::iterator _itr) :
				pool_{ _pool },
				used_{ _used },
				itr_{ _itr }
			{}
			~PoolIterator() {}

			size_t GetIndex() const { return itr_ - pool_.begin(); }

			// 前置インクリメント
			PoolIterator& operator++()
			{
				while (true)
				{
					itr_++;
					if (itr_ == pool_.end())
					{
						break;
					}

					if (used_[GetIndex()])
					{
						break;
					}
				}

				return *this;
			}

			// 後置インクリメント
			PoolIterator operator++(int)
			{
				while (true)
				{
					itr_++;
					if (itr_ == pool_.end())
					{
						break;
					}

					if (used_[GetIndex()])
					{
						break;
					}
				}

				return *this;
			}

			bool operator==(const PoolIterator& _other) const
			{
				return this->itr_ == _other.itr_;
			}

			bool operator!=(const PoolIterator& _other) const
			{
				return !(*this == _other);
			}

			ComponentT& operator*() const
			{
				return *itr_;
			}

			PoolIterator operator+(const size_t _index) const
			{
				PoolIterator itr{ *this };
				itr.itr_ += _index;
				return itr;
			}

		protected:
			Pool::iterator itr_;
			const Pool& pool_;
			const std::bitset<ENTITY_CAPACITY>& used_;
		};

		class ConstPoolIterator
		{
		public:
			ConstPoolIterator(const Pool& _pool, const std::bitset<ENTITY_CAPACITY>& _used, Pool::const_iterator _itr) :
				pool_{ _pool },
				used_{ _used },
				itr_{ _itr }
			{
			}
			~ConstPoolIterator() {}

			size_t GetIndex() const { return itr_ - pool_.begin(); }

			// 前置インクリメント
			ConstPoolIterator& operator++()
			{
				while (true)
				{
					itr_++;
					if (itr_ == pool_.end())
					{
						break;
					}

					if (used_[GetIndex()])
					{
						break;
					}
				}

				return *this;
			}

			// 後置インクリメント
			ConstPoolIterator operator++(int)
			{
				while (true)
				{
					itr_++;
					if (itr_ == pool_.end())
					{
						break;
					}

					if (used_[GetIndex()])
					{
						break;
					}
				}

				return *this;
			}

			bool operator==(const ConstPoolIterator& _other) const
			{
				return this->itr_ == _other.itr_;
			}

			bool operator!=(const ConstPoolIterator& _other) const
			{
				return !(*this == _other);
			}

			const ComponentT& operator*() const
			{
				return *itr_;
			}

			ConstPoolIterator operator+(const size_t _index) const
			{
				ConstPoolIterator itr{ *this };
				itr.itr_ += _index;
				return itr;
			}

		protected:
			Pool::const_iterator itr_;
			const Pool& pool_;
			const std::bitset<ENTITY_CAPACITY>& used_;
		};

	protected:
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
	
	public:
		/// <summary>
		/// 終了処理
		/// </summary>
		virtual void End() override {}

		template<typename T = ComponentT, typename ...Args>
		ComponentT& Add(const EntityId _entityId, const Args& ...args);

		/// <summary>
		/// <para>コンポーネントを取得する</para>
		/// <para>NOTE: 返されたポインタを保存しないでください！</para>
		/// </summary>
		/// <param name="_entityId">エンティティId</param>
		/// <returns>コンポーネントのポインタ / なければ nullptr</returns>
		[[nodiscard]]
		std::remove_pointer_t<ComponentT>* Get(const EntityId _entityId);

		/// <summary>
		/// エンティティのコンポーネントをはずす
		/// </summary>
		/// <param name="_entityId">外すエンティティId</param>
		void Remove(const EntityId _entityId);

		/// <summary>
		/// 全コンポーネントを破棄する
		/// </summary>
		void Clear() override;

		/// <summary>
		/// 指定のコンポーネントを破棄する
		/// </summary>
		/// <param name="_index">指定のインデクス</param>
		void ClearAt(const size_t _index) override;

		void ForEach(const std::function<void(ComponentT&)>& _callback);
		void ForEach(const std::function<void(ComponentT&, const size_t)>& _callback);
		void ForEach(const std::function<void(const ComponentT&)>& _callback) const;
		void ForEach(const std::function<void(const ComponentT&, const size_t)>& _callback) const;

	protected:
		/// <summary>
		/// 初期化処理
		/// </summary>
		virtual void Init() = 0;
		/// <summary>
		/// 更新処理
		/// </summary>
		virtual void Update() = 0;

		const ViewerCached& System() const { return system_; }
		ViewerCached& System() { return system_; }

	protected:
		/*PoolIterator begin() { return { pool_, useFlag_, GetUsedBeginItr() }; }
		PoolIterator end() { return { pool_, useFlag_, pool_.end() }; }
		ConstPoolIterator begin() const { return { pool_, useFlag_, GetUsedBeginItr() }; }
		ConstPoolIterator end() const { return { pool_, useFlag_, pool_.end() }; }*/

		inline ComponentT& at(const size_t _index) { return pool_.at(_index); }
		inline ComponentT& at(const EntityId _entityId) { assert(!IsInvalidEntity(_entityId) && "無効なエンティティ"); return pool_.at(_entityId.index); }
		inline const ComponentT& at(const size_t _index) const { return pool_.at(_index); }
		inline const ComponentT& at(const EntityId _entityId) const { return assert(!IsInvalidEntity(_entityId) && "無効なエンティティ"); pool_.at(_entityId.index); }

		inline const ComponentT* DataBegin() const { return pool_.data(); }
	private:
		/// <summary>
		/// 使われている itr begin を取得する
		/// </summary>
		/// <returns>プールのイテレータ</returns>
		Pool::iterator GetUsedBeginItr();
		/// <summary>
		/// 使われている itr begin を取得する
		/// </summary>
		/// <returns>プールのイテレータ</returns>
		Pool::const_iterator GetUsedBeginItr() const;

		bool IsInvalidEntity(const EntityId _entityId);

	private:
		Pool pool_;
		std::bitset<ENTITY_CAPACITY> useFlag_;  // エンティティがコンポーネントを使用しているかフラグ
		ViewerCached system_;
	};
}

#include "ComponentPool.inl"
