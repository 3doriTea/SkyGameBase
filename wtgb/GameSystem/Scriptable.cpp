#include "pch/pch.h"
#include "Scriptable.h"
#include "Core/GameObjectBuilder.h"

#include "CoreType/ExtJson/Vector3.h"

#include "GameComponent/Transform.h"
#include "GameComponent/GameObjectProperty.h"
#include "GameComponent/ModelMesh.h"
#include "GameComponent/MeshRenderer.h"

#include "WTGBAssert.h"

wtgb::Scriptable::Scriptable() :
	system_{ nullptr }
{
}

wtgb::Scriptable::~Scriptable()
{
}

wtgb::Result wtgb::Scriptable::Init(const ViewerInit& _viewer)
{
	system_ = _viewer.GetCache();
	return Result::Code::Ok;
}

void wtgb::Scriptable::Update(const ViewerUpdate& _system)
{
}

void wtgb::Scriptable::End()
{
}

void wtgb::Scriptable::LoadPrefabFromJson(const fs::path& _jsonPath, GameObjectBuilder& _builder)
{
	ComponentManager& cm{ System().Get<ComponentManager>() };

	std::ifstream ifs{ "./Prefab" / _jsonPath };

	wassert(ifs && "プレファブファイルの読み込みに失敗 jsonファイル名が正しいか確認して");

	json j{};
	ifs >> j;
	ifs.close();

	json& components{ j.at("Component") };

	// TODO: ここの手作業を省く ex:コンポーネント側にjsonの入力関数をつけておく？
	for (auto& component : components.items())
	{
		const std::string& componentName{ component.key() };

		if (componentName == "Transform")
		{
			_builder
				.AddComponent<Transform>()
					.BeginSetter()
						.position(component.value().at("position").get<Vector3>())
						.rotation(component.value().at("rotation").get<Vector3>())
						.scale(component.value().at("scale").get<Vector3>())
					.EndSetter();
		}
		else if (componentName == "GameObjectProperty")
		{
			_builder
				.AddComponent<GameObjectProperty>()
				.BeginSetter()
				.name(component.value().at("name").get<std::string>())
				.EndSetter();
		}
		else if (componentName == "ModelMesh")
		{
			_builder
				.AddComponent<ModelMesh>()
				.BeginSetter()
				.fileName(component.value().at("fileName").get<std::string>())
				.EndSetter();
		}
		else if (componentName == "MeshRenderer")
		{
			_builder
				.AddComponent<MeshRenderer>()
				.BeginSetter()
				.shader(component.value().at("shader").get<std::string>())
				.EndSetter();
		}
		else
		{
			wassert(false && "未対応のコンポーネントを処理できません");
		}
	}
	_builder.Build();
}
