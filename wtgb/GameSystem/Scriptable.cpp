#include "pch/pch.h"
#include "Scriptable.h"
#include "Core/GameObjectBuilder.h"

#include "CoreType/ExtJson/Vector3.h"

#include "GameComponent/Transform.h"
#include "GameComponent/GameObjectProperty.h"

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

	json j{};
	ifs >> j;
	ifs.close();

	json& components{ j.at("Component") };

	// TODO: ここの手作業を省く ex:コンポーネント側にjsonの入力関数をつけておく？
	for (auto& component : components.items())
	{
		if (component.key() == "Transform")
		{
			_builder
				.AddComponent<Transform>()
					.BeginSetter()
						.position(component.value().at("position").get<Vector3>())
						.rotation(component.value().at("rotation").get<Vector3>())
						.scale(component.value().at("scale").get<Vector3>())
					.EndSetter();
		}
		else if (component.key() == "GameObjectProperty")
		{
			_builder
				.AddComponent<GameObjectProperty>()
				.BeginSetter()
				.name(component.value().at("name").get<std::string>())
				.EndSetter();
		}
	}
	j.at("GameObjectProperty");
}
