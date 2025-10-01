#pragma once
#include "pch\pch.h"
#include "IGameSystem.h"

namespace wtgb
{
	template<typename T>
	concept GameSystemT = std::is_base_of_v<IGameSystem, T>;

	/// <summary>
	/// ゲームシステムをまとめるクラス
	/// </summary>
	class GameSystemCollection
	{
	public:
		GameSystemCollection() {}
		~GameSystemCollection();

		/// <summary>
		/// ゲームシステムを登録する
		/// </summary>
		/// <typeparam name="T">ゲームシステムの型</typeparam>
		/// <returns>GameSystemCollection自己参照</returns>
		template<GameSystemT T>
		GameSystemCollection& Register();

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
		void UpdateForEach(const std::vector<int>& _indexRef);
		/// <summary>
		/// 登録されている全ゲームシステムを初期化する
		/// </summary>
		void InitForEachAll();
		/// <summary>
		/// 登録されている全ゲームシステムを終了処理する
		/// </summary>
		void EndForEachAll();

	private:
		std::vector<IGameSystem*> gameSystems_;  // 登録したゲームシステム
		std::vector<int> callFrameIndexes_;  // 描画フレームで呼び出すゲームシステムの要素番号
		std::vector<int> callCycleIndexes_;  // ゲームループサイクルで呼び出すゲームシステムの要素番号
	};
}

template<wtgb::GameSystemT T>
inline wtgb::GameSystemCollection& wtgb::GameSystemCollection::Register()
{
	IGameSystem* pGameSystem{ new T{} };

	const int index{ gameSystems_.size() };

	gameSystems_.push_back(pGameSystem);
	
	// 呼び出すタイミング別で要素番号を保存しておく
	switch (pGameSystem->GetCallType())
	{
	case IGameSystem::CallType::Frame:
		callFrameIndexes_.push_back(index);
		break;
	case IGameSystem::CallType::Cycle:
		callCycleIndexes_.push_back(index);
		break;
	default:
		break;
	}

	return *this;
}
