#pragma once
#include "pch/pch.h"
#include "CommonGameComponent.h"
#include "GameSystem/CPModelMesh.h"

namespace wtgb
{

	class COMPONENT(ModelMesh)
	{
	public:
		class SETTER(ModelMesh)
		{
			SETTER_HEAD(ModelMesh)

			SETTER_PARAM(std::string, fileName)
		};

	public:
		ModelMesh() {}
		~ModelMesh() {}

		void Load();

		void Init(ViewerCached system_) override;
		void Update(ViewerCached system_) override {}

	private:
		std::string fileName_;
	};
}
