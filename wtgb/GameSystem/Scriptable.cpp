#include "pch/pch.h"
#include "Scriptable.h"
#include "Core/GameObjectBuilder.h"

#include "CoreType/ExtJson/Vector3.h"
#include "Utility/JsonUtility.h"

#include "GameComponent/Transform.h"
#include "GameComponent/GameObjectProperty.h"
#include "GameComponent/ModelMesh.h"
#include "GameComponent/MeshRenderer.h"
#include "GameComponent/RigidBody.h"
#include "GameComponent/Collider.h"
#include "GameComponent/Parameter.h"

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

	fs::path inPrefabPath{ "./Prefab" / _jsonPath };

	wassert(fs::is_regular_file(inPrefabPath) && "jsonファイルが正しく読み込めていない");

	std::ifstream ifs{ inPrefabPath };

	wassert(!!ifs && "プレファブファイルの読み込みに失敗 jsonファイル名が正しいか確認して");

	json j{};
	try
	{
		ifs >> j;
	}
	catch (const std::exception&)
	{
		wassert(false && "jsonファイルのフォーマットエラー");
		return;
	}
	ifs.close();


	json* pComponents{ nullptr };
	if (TryGet("Component", &pComponents, j))
	{
		LoadComponents(_builder, *pComponents);
	}

	// Parameterコンポーネントは特別
	// json内 Components に書かずとも Param があればコンポーネントとして追加
	json* pParams{ nullptr };
	if (TryGet("Param", &pParams, j))
	{
		_builder.AddComponent<Parameter>()
			.BeginSetter()
				.jsonFilePath(inPrefabPath)
			.EndSetter();
	}

	_builder.Build();
}

void wtgb::Scriptable::LoadComponents(GameObjectBuilder& _builder, json& _components)
{
	// TODO: ここの手作業を省く ex:コンポーネント側にjsonの入力関数をつけておく？
	for (auto& component : _components.items())
	{
		const std::string& componentName{ component.key() };

		if (componentName == "Transform")
		{
			_builder
				.AddComponent<Transform>()
				.BeginSetter()
				.position(SafeGet<Vector3>(component.value(), "position"))
				.rotation(SafeGet<Vector3>(component.value(), "rotation"))
				.scale(SafeGet<Vector3>(component.value(), "scale"))
				.EndSetter();
		}
		else if (componentName == "GameObjectProperty")
		{
			_builder
				.AddComponent<GameObjectProperty>()
				.BeginSetter()
				.name(SafeGet<std::string>(component.value(), "name"))
				.EndSetter();
		}
		else if (componentName == "ModelMesh")
		{
			_builder
				.AddComponent<ModelMesh>()
				.BeginSetter()
				.fileName(SafeGet<std::string>(component.value(), "fileName"))
				.modelMeshType(static_cast<ModelMesh::Type>(SafeGet<int>(component.value(), "modelMeshType")))
				.EndSetter();
		}
		else if (componentName == "MeshRenderer")
		{
			_builder
				.AddComponent<MeshRenderer>()
				.BeginSetter()
				.shader(SafeGet<std::string>(component.value(), "shader"))
				.texture(SafeGet<std::string>(component.value(), "texture"))
				.EndSetter();
		}
		else if (componentName == "RigidBody")
		{
			_builder
				.AddComponent<RigidBody>()
				.BeginSetter()
				.mass(SafeGet<float>(component.value(), "mass"))
				.bounciness(SafeGet<float>(component.value(), "bounciness"))
				.useGravity(SafeGet<bool>(component.value(), "useGravity"))
				.angularDrag(SafeGet<float>(component.value(), "angularDrag"))
				.angularVelocity(SafeGet<Vector3>(component.value(), "angularVelocity"))
				.velocity(SafeGet<Vector3>(component.value(), "velocity"))
				.EndSetter();
		}
		else if (componentName == "Collider")
		{
			_builder
				.AddComponent<Collider>()
				.BeginSetter()
				.colliderType(static_cast<Collider::Type>(SafeGet<int>(component.value(), "colliderType")))
				.EndSetter();
		}
		else if (componentName == "Param")
		{
			wassert(false && "Paramはコンポーネントとして追加できません。");
		}
		else
		{
			wassert(false && "未対応のコンポーネントを処理できません");
		}
	}
}
