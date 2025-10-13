#pragma once
#include "pch\pch.h"
#include "IGameSystem.h"
#include <typeindex>
#include <map>

namespace wtgb
{
	template<typename T>
	concept GameSystemT = std::is_base_of_v<IGameSystem, T>;

	/// <summary>
	/// ゲームシステムをまとめるクラス
	/// </summary>
	class GameSystemCollection
	{
	private:
		/// <summary>
		/// 登録されているゲームシステムのインデックス
		/// </summary>
		using Index = size_t;
		/// <summary>
		/// 型インデックスからゲームシステムのインデックスへアクセス用連想配列
		/// </summary>
		using TypeKeys = std::map<std::type_index, Index>;
		/// <summary>
		/// 登録されるゲームシステムの配列
		/// </summary>
		using GameSystems = std::vector<IGameSystem*>;
		/// <summary>
		/// 登録されているゲームシステムのインデックス配列
		/// </summary>
		using Indexes = std::vector<Index>;

	public:
		/// <summary>
		/// ゲームシステムにアクセスする基底クラス
		/// </summary>
		class GameSystemAccessor
		{
		public:
			GameSystemAccessor(GameSystemCollection* _pGameSystemCollection);
			virtual ~GameSystemAccessor() {};

		protected:
			GameSystemCollection* pGameSystemCollection_;
		};

		/// <summary>
		/// ゲームシステムにアクセスし追加だけするクラス
		/// </summary>
		class GameSystemAdder : public GameSystemAccessor
		{
		public:
			using GameSystemAccessor::GameSystemAccessor;
			~GameSystemAdder() {};

			// <summary>
			/// ゲームシステムにアクセスし登録だけするクラス
			/// </summary>
			/// <typeparam name="T">ゲームシステムの型</typeparam>
			/// <returns>GameSystemAdder自己参照</returns>
			template<GameSystemT T, typename ...Args>
			const GameSystemAdder& Register(Args&& ...args) const;
		};

		/// <summary>
		/// ゲームシステムの参照だけクラス
		/// </summary>
		class GameSystemViewer : public GameSystemAccessor
		{
		public:
			using GameSystemAccessor::GameSystemAccessor;
			~GameSystemViewer() {};

			/// <summary>
			/// 指定した型のゲームシステムを取得する
			/// </summary>
			/// <typeparam name="T">指定する型</typeparam>
			/// <returns>ゲームシステム</returns>
			template<GameSystemT T>
			T& Get() const;
		};

	public:
		GameSystemCollection() {}
		~GameSystemCollection();

		/// <summary>
		/// 登録された全ゲームシステムを初期化する
		/// </summary>
		void Init() { InitForEachAll(); }
		/// <summary>
		/// フレーム呼び出しとして登録されたゲームシステムを更新
		/// </summary>
		void UpdateFrame() { UpdateForEach(callFrameIndexes_); }
		/// <summary>
		/// サイクル呼び出しとして登録されたゲームシステムを更新
		/// </summary>
		void UpdateCycle() { UpdateForEach(callCycleIndexes_); }
		/// <summary>
		/// 登録されている全ゲームシステムを終了する
		/// </summary>
		void End() { EndForEachAll(); }

	private:
		/// <summary>
		/// ゲームシステムを更新する
		/// </summary>
		/// <param name="_indexRef">呼び出す要素番号の参照</param>
		void UpdateForEach(const Indexes& _indexRef);
		/// <summary>
		/// 登録されている全ゲームシステムを初期化する
		/// </summary>
		void InitForEachAll();
		/// <summary>
		/// 登録されている全ゲームシステムを終了処理する
		/// </summary>
		void EndForEachAll();

	private:
		TypeKeys gameSystemTypeKey_;  // ゲームシステムの型キー
		GameSystems gameSystems_;     // 登録したゲームシステム
		Indexes callFrameIndexes_;    // 描画フレームで呼び出すゲームシステムの要素番号
		Indexes callCycleIndexes_;    // ゲームループサイクルで呼び出すゲームシステムの要素番号
	};
}

template<wtgb::GameSystemT T, typename ...Args>
inline const wtgb::GameSystemCollection::GameSystemAdder&
	wtgb::GameSystemCollection::GameSystemAdder::Register(Args&& ...args) const
{
	assert(pGameSystemCollection_ && "ゲームシステムコレクションがnullptr参照されてしまう");

	// コレクション要素への参照
	TypeKeys& gameSystemTypeKey{ pGameSystemCollection_->gameSystemTypeKey_ };
	GameSystems& gameSystems   { pGameSystemCollection_->gameSystems_ };
	Indexes& callFrameIndexes  { pGameSystemCollection_->callFrameIndexes_ };
	Indexes& callCycleIndexes  { pGameSystemCollection_->callCycleIndexes_ };

	IGameSystem* pGameSystem{ new T{ args... } };

	const Index index{ gameSystems.size() };

	gameSystems.push_back(pGameSystem);
	gameSystemTypeKey.emplace(typeid(T), index);
	
	// 呼び出すタイミング別で要素番号を保存しておく
	switch (pGameSystem->GetCallType())
	{
	case IGameSystem::CallType::Frame:
		callFrameIndexes.push_back(index);
		break;
	case IGameSystem::CallType::Cycle:
		callCycleIndexes.push_back(index);
		break;
	default:
		break;
	}

	return *this;
}

template<wtgb::GameSystemT T>
inline T& wtgb::GameSystemCollection::GameSystemViewer::Get() const
{
	TypeKeys& gameSystemTypeKey{ pGameSystemCollection_->gameSystemTypeKey_ };
	GameSystems& gameSystems{ pGameSystemCollection_->gameSystems_ };

	Index index{};
	try
	{
		index = gameSystemTypeKey.at(typeid(T));
	}
	catch (const std::out_of_range& exception)
	{
		(void)exception;  // 意図的に使っていないよ！
		// 型が登録されていない
		assert(false && "指定されたゲームシステム型が登録されていない");
	}

	IGameSystem* pGameSystem{};
	try
	{
		pGameSystem = gameSystems.at(index);
	}
	catch (const std::out_of_range& exception)
	{
		(void)exception;  // 意図的に使っていないよ！
		// 型からindexは取得済み、実体へのポインタが未登録
		assert(false && "指定されたゲームシステムが登録されていない");
	}

	T* p{ dynamic_cast<T*>(pGameSystem) };
	assert(p != nullptr && "指定された型がゲームシステムではない @wtgb::GameSystemCollection::Get");

	return *p;
}
