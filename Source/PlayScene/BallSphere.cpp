#include "BallSphere.h"

BallSphere::BallSphere(const EntityId _targetChara) :
	GameObject{ "Play/BallSphere.json" }
	/*GameObject
	{
		[](GameObjectBuilder& _builder)
		{
			_builder
				.AddComponent<ModelMesh>()
				.BeginSetter()
					.fileName("Models/Sphere/Sphere.fbx")
					.modelMeshType(ModelMesh::Type::FbxAplha)
				.EndSetter()
			.Build();
		}
	}*/
{
	// 追従するために親子関係を結ぶ
	Property().SetParent(_targetChara);
}

BallSphere::~BallSphere()
{
}

void BallSphere::Init()
{
}

void BallSphere::Update()
{
}

void BallSphere::Release()
{
}
