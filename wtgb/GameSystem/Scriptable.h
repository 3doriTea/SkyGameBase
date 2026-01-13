#pragma once
#include "Core/IGameSystem.h"

namespace wtgb
{
	class GameObjectBuilder;

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

		Result Init(const ViewerInit& _viewer) override;

		void Update(const ViewerUpdate& _system) override;

		void End() override;

		void LoadPrefabFromJson(const fs::path& _jsonPath, GameObjectBuilder& _builder);

		inline ViewerCached& System() { return system_; }

	private:
		/// <summary>
		/// 指定キーのJsonオブジェクトがあれば取得する
		/// </summary>
		/// <param name="_key">指定するキー</param>
		/// <param name="_ppDistJson">あれば参照が取れる</param>
		/// <param name="_srcJson">取得するjsonオブジェクト</param>
		/// <returns>あるか true / false</returns>
		bool TryGet(const std::string_view _key, json** _ppDistJson, json& _srcJson);

		/// <summary>
		/// ゲームオブジェクトに付けるコンポーネントを読み込んでいく
		/// </summary>
		/// <param name="_builder">ビルド中のゲームオブジェクト</param>
		/// <param name="_components">コンポーネント部分のjsonオブジェクト</param>
		void LoadComponents(GameObjectBuilder& _builder, json& _components);

	private:
		ViewerCached system_;
	};
}
