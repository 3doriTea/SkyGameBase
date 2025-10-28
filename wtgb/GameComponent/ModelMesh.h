#pragma once
#include "pch/pch.h"
#include "Core/Component.h"
#include "Core/ComponentSetter.h"
#include "GameSystem/CPModelMesh.h"

namespace wtgb
{

	class ModelMesh : public Component<CPModelMesh>
	{
	public:
		class Setter : public ComponentSetter<ModelMesh>
		{
		public:
			using ComponentSetter<ModelMesh>::ComponentSetter;
			~Setter() {}

			Setter& Model(const std::string& _fileName) { GetAccess()-> }

		};

	public:
		ModelMesh() {}
		~ModelMesh() {}

		void Load();
		void Update() override {}

	private:
		std::string fileName_;
	};
}
