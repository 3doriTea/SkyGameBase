#pragma once
#include "Core/IGameSystem.h"

namespace wtgb
{
	class GameObjectBuilder;

	/// <summary>
	/// JSONファイルからゲームオブジェクトを読み込むシステム
	/// </summary>
	class Scriptable : public IGameSystem
	{
	public:
		Scriptable();
		~Scriptable();

		/// <summary>
		/// 更新のタイミング
		/// </summary>
		/// <returns>更新のタイミング</returns>
		const CallType GetCallType() override { return CallType::Frame; }

		/// <summary>
		/// 初期化処理
		/// </summary>
		/// <param name="_viewer">システムの参照</param>
		/// <returns>初期化処理の結果</returns>
		Result Init(const ViewerInit& _viewer) override;

		/// <summary>
		/// 更新処理
		/// </summary>
		/// <param name="_system">システムの参照</param>
		void Update(const ViewerUpdate& _system) override;

		/// <summary>
		/// 終了処理
		/// </summary>
		void End() override;

		/// <summary>
		/// JSONファイルからゲームオブジェクトを読み込む
		/// </summary>
		/// <param name="_jsonPath">JSONファイルのパス</param>
		/// <param name="_builder">ゲームオブジェクトビルダー</param>
		void LoadPrefabFromJson(const fs::path& _jsonPath, GameObjectBuilder& _builder);

		/// <summary>
		/// システム参照
		/// </summary>
		/// <returns>参照ポインタ</returns>
		inline ViewerCached& System() { return system_; }

	private:
		/// <summary>
		/// ゲームオブジェクトに付けるコンポーネントを読み込んでいく
		/// </summary>
		/// <param name="_builder">ビルド中のゲームオブジェクト</param>
		/// <param name="_components">コンポーネント部分のjsonオブジェクト</param>
		void LoadComponents(GameObjectBuilder& _builder, json& _components);

	private:
		ViewerCached system_;  // システムへの参照
	};
}
