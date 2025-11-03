#pragma once
#include "Core/IGameSystem.h"
#include "ModelMesh/ModelResource.h"

namespace wtgb
{
	class Model : public IGameSystem
	{
	public:
		Model();
		~Model();

		/// <summary>
		/// 更新タイミングを取得
		/// </summary>
		/// <returns>更新しない</returns>
		const CallType GetCallType() override { return CallType::DoNotUpdate; }
		/// <summary>
		/// 初期化処理
		/// </summary>
		/// <param name="_viewer">システムへのビュア</param>
		/// <returns>初期化処理の結果</returns>
		Result Init(const ViewerInit& _viewer) override;
		/// <summary>
		/// 更新処理
		/// </summary>
		/// <param name="_system">システムへのビュア</param>
		void Update(const ViewerUpdate& _system) override;
		/// <summary>
		/// 終了処理
		/// </summary>
		void End() override;

		void Load(const std::string& _fileName);

	private:
		ViewerCached system_;  // システムアクセス用
		HandlerCollection<ModelResource*, ModelHandle> models_;  // モデルハンドラコレクション
	};
}
