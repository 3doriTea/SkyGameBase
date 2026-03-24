#include "LiftChild.h"

LiftChild::LiftChild(
	const EntityId _parentLift,
	const fs::path& _modelFile) :
	GameObject{ "LiftChild.json" }
{
}

LiftChild::~LiftChild()
{
}

void LiftChild::SetModel(const ModelHandle _hModel)
{
	ModelMesh& modelMesh{ GetComponent<ModelMesh>() };
	modelMesh.SetModel(_hModel);
	modelMesh.Reflesh(System());
}

void LiftChild::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());
}

void LiftChild::Update()
{
}

void LiftChild::Release()
{
}
