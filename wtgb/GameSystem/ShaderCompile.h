#pragma once
#include "Core/IGameSystem.h"

namespace wtgb
{
	using ShaderHandle = uint32_t;
	class ShaderCompile : public IGameSystem
	{
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


		const ShaderHandle Compile(const std::string& _fileNmae);

	private:
		HandlerCollection<ShaderHandle> shaderHandles_;
	};
}
