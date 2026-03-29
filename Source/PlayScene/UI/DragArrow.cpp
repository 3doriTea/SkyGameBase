#include "DragArrow.h"


DragArrow::DragArrow(const EntityId _axis) :
	GameObject{ "Play/DragArrow.json" },
	axis_{ _axis }
{
	GetComponent<GameObjectProperty>().SetParent(axis_);
	Transform().SetRotation(Vector3::Up() * DirectX::XM_PI);
	Transform().SetPosition(Vector3::Forward() * 0.5f);
}

DragArrow::~DragArrow()
{
}

void DragArrow::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());
}

void DragArrow::Update()
{
}

void DragArrow::Release()
{
}

void DragArrow::ChangeType(const DragArrowType _type)
{
	type_ = _type;
	switch (_type)
	{
	case DragArrowType_Control:
	case DragArrowType_Velocity:
		GetComponent<MeshRenderer>().SetTexture(hTexture_[_type]);
		break;
	case DragArrowType_Max:
	default:
		wassert(false && "未対応の矢印タイプ");
		break;
	}
}

void DragArrow::OnLoadParam(const json& _json)
{
	hTexture_[DragArrowType_Control] =
		System().Get<wtgb::ResourceSystem>().LoadTexture(
			SafeGet<std::string>(_json, "dragArrowImageFilePath"));

	wassert(hTexture_[DragArrowType_Control] != INVALID_HANDLE
		&& "操作矢印テクスチャの読み込み失敗");

	hTexture_[DragArrowType_Velocity] =
		System().Get<wtgb::ResourceSystem>().LoadTexture(
			SafeGet<std::string>(_json, "veloArrowImageFilePath"));

	wassert(hTexture_[DragArrowType_Velocity] != INVALID_HANDLE
		&& "速度矢印テクスチャの読み込み失敗");
}
