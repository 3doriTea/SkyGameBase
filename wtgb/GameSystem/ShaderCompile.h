#pragma once
#include "Core/IGameSystem.h"
#include "ShaderCompile/Shader.h"
#include "Utility/Accessor.h"

namespace wtgb
{
	// TODO: シェーダ コンパイル -> コンパイラーに名前変更を考える
	class ShaderCompile : public IGameSystem
	{
		friend class Direct3D;
	public:
		/// <summary>
		/// シェーダをコンパイルするときの設定
		/// </summary>
		struct CompileConfig
		{
			/// <summary>
			/// 各シェーダ固有の指定
			/// </summary>
			struct ShaderTarget
			{
				std::string entryPointName;  // エントリポイント名
				std::string compileVersion;  // シェーダのバージョン
			};

			std::string fileName;  // ファイル名

			ShaderTarget vertexShader;  // 頂点シェーダ固有の指定
			ShaderTarget pixelShader;   // ピクセルシェーダ固有の指定

			std::vector<D3D11_INPUT_ELEMENT_DESC> vertexInputLayout;  // 頂点インプットレイアウト


			D3D11_FILL_MODE fillMode;  // 塗りつぶしモード
			D3D11_CULL_MODE cullMode;  // 陰面消去モード
			bool backIsClockwise;  // 時計回りを裏面とするか

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
		Shader::ShaderAccessor& GetShader(const ShaderHandle _hShader);

	private:
		HandlerCollection<Shader, ShaderHandle> shaders_;  // シェーダコレクション
		ViewerCached system_;  // システムにアクセスするようのキャッシュ
	};
}
