#pragma once
#include "pch\pch.h"
#include <typeindex>
#include <map>

#include "GameSystem/IComponentPool.h"
#include "Utility/Accessor.h"

namespace wtgb
{
	class IGameSystem;

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
		using GameSystemAccessor = Accessor<GameSystemCollection>;

		/// <summary>
		/// <para>ゲームシステムにアクセスし追加だけするクラス</para>
		/// <para>追加後自己参照を返すため、関数型のように書ける</para>
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
			template<typename T, typename ...Args>
			const GameSystemAdder& Register(Args&& ...args) const;
		};

		/// <summary>
		/// ゲームシステムのうちコンポーネントプールにアクセスするだけのクラス
		/// </summary>
		class ComponentPoolAccessor : public Accessor<GameSystemCollection>
		{
			friend class ComponentManager;
		public:
			/// <summary>
			/// <para>走査するコールバック関数</para>
			/// <para>void(IComponentPool*)</para>
			/// </summary>
			using ForEachCallback = std::function<void(IComponentPool*)>;

		public:
			using Accessor<GameSystemCollection>::Accessor;
			~ComponentPoolAccessor() {}

			/// <summary>
			/// 登録されている	全コンポーネントプールを走査
			/// </summary>
			/// <param name="_callback">void(IComponentPool*)</param>
			void ForEachAll(const ForEachCallback& _callback);
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
			template<typename T>
			[[nodiscard]]
			T& Get() const;
		};

		/// <summary>
		/// <para>各ゲームオブジェクトへ参照だけ提供</para>
		/// <para>メンバ変数として保持しておく用</para>
		/// </summary>
		class GameSystemCachedViewer : public GameSystemViewer
		{
		public:
			using GameSystemViewer::GameSystemViewer;
			~GameSystemCachedViewer() {};
		};

		/// <summary>
		/// ゲームシステム初期化の時の参照だけ提供
		/// </summary>
		class GameSystemInitViewer : public GameSystemViewer
		{
		public:
			using GameSystemViewer::GameSystemViewer;
			~GameSystemInitViewer() {};

			GameSystemCachedViewer GetCache() const;
		};

		/// <summary>
		/// ゲームシステム更新の時の参照だけ提供
		/// </summary>
		class GameSystemUpdateViewer : public GameSystemViewer
		{
		public:
			using GameSystemViewer::GameSystemViewer;
			~GameSystemUpdateViewer() {};
		};

	public:
		GameSystemCollection();
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

		// TODO: クラス分けする
		Indexes componentPoolIndexes_;  // コンポーネントプールの要素番号
	};
}

#include "GameSystemCollection.inl"
