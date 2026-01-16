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
		/// ‰Šú‰»ˆ—
		/// </summary>
		void Init(ViewerCached _system) override {}
		/// <summary>
		/// XVˆ—
		/// </summary>
		void Update(ViewerCached _system) override {}

		/// <summary>
		/// json“Ç‚İ‚İ
		/// </summary>
		/// <returns>“Ç‚İ‚ñ‚¾Json‚ÌQÆ</returns>
		const json& Load();

	private:
		fs::path jsonFilePath_;
		json json_;
	};
}
