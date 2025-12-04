#pragma once
#include "Core/IGameSystem.h"

namespace wtgb
{
	class IMeshSimple;

	/// <summary>
	/// デバッグを管理するシステム
	/// </summary>
	class Debug : public IGameSystem
	{
	public:
		Debug();
		~Debug();

		/// <summary>
		/// 更新のタイミング
		/// </summary>
		/// <returns>更新のタイミング</returns>
		const CallType GetCallType() override { return CallType::Frame; }

		/// <summary>
		/// 初期化処理
		/// </summary>
		Result Init(const ViewerInit& _viewer) override;
		/// <summary>
		/// 更新処理
		/// </summary>
		void Update(const ViewerUpdate& _system) override;
		/// <summary>
		/// 終了処理
		/// </summary>
		void End() override;

		ViewerCached& System() { return system_; }

		/// <summary>
		/// デバッグ用球体モデルを取得
		/// </summary>
		/// <returns></returns>
		IMeshSimple* GetDebugSphere();
		/// <summary>
		/// デバッグ用シェーダを取得
		/// </summary>
		/// <returns>デバッグシェーダの取得</returns>
		inline ShaderHandle GetDebugShader() const { return hShader_; }

	#pragma region 任意の点についてのデバッグ
		static void DrawPoint(const Vector3& _position);
	#pragma endregion

	#pragma region コンポーネントオプションのカウント
		static size_t& ComponentOptInstanceCount() { return componentOptInstanceCount_; }

		static size_t componentOptInstanceCount_;
	#pragma endregion

	private:
		ModelHandle hTestPointSphere_;   // テスト用球モデル
		ShaderHandle hTestPointShader_;  // デバッグ用シェーダ

		ModelHandle hSphere_;  // デバッグ用球モデル
		ShaderHandle hShader_;  // デバッグ用シェーダ

		ViewerCached system_;  // システムのキャッシュ

		static Debug* pInstance_;  // デバッグ時のみシングルトン
	};
}
