#pragma once
#include "Core/IGameSystem.h"
#include "ShaderCompile/Shader.h"

namespace wtgb
{
	// TODO: シェーダ コンパイル -> コンパイラーに名前変更を考える

	using ShaderHandle = uint32_t;
	class ShaderCompile : public IGameSystem
	{
	public:
		/// <summary>
		/// シェーダをコンパイルするときの設定
		/// </summary>
		struct CompileConfig
		{
			/// <summary>
			/// 各シェーダ固有の指定
			/// </summary>
			struct Target
			{
				std::string entryPointName;  // エントリポイント名
				std::string compileVersion;  // シェーダのバージョン
			};

			Target target;  // 各シェーダ固有の指定

			std::string fileName;  // ファイル名

			UINT flag1{ 0 };  // フラグ1
			UINT flag2{ 0 };  // フラグ2

			D3D_SHADER_MACRO* pDefines{ nullptr };  // マクロ(定義)ファイル
			ID3DInclude* pInclude{ nullptr };       // インクルードファイル
		};

	public:
		ShaderCompile();
		~ShaderCompile();

		/// <summary>
		/// 更新のタイミング
		/// </summary>
		/// <returns>更新のタイミング</returns>
		const CallType GetCallType() { return CallType::Frame; }

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


		const ShaderHandle Compile(const CompileConfig& _config);

	private:
		HandlerCollection<Shader, ShaderHandle> shaders_;  // シェーダコレクション
		ViewerCached system_;  // システムにアクセスするようのキャッシュ
	};
}
