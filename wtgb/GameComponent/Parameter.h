#pragma once
#include "Helper/CommonGameComponent.h"
#include "LibHeader/FileSystem.h"
#include "GameSystem/CPParameter.h"

namespace wtgb
{
	class COMPONENT(Parameter)
	{
		COMPONENT_HEAD(Parameter)
	public:
		class SETTER(Parameter)
		{
			SETTER_HEAD(Parameter)

			SETTER_PARAM(fs::path, jsonFilePath);
		};

	public:
		Parameter();
		inline ~Parameter() {}

		/// <summary>
		/// 初期化処理
		/// </summary>
		void Init(ViewerCached _system) override {}
		/// <summary>
		/// 更新処理
		/// </summary>
		void Update(ViewerCached _system) override {}

		/// <summary>
		/// json読み込み
		/// </summary>
		/// <returns>読み込んだJsonの参照</returns>
		const json& Load();

	private:
		fs::path jsonFilePath_;
		json json_;
	};
}
