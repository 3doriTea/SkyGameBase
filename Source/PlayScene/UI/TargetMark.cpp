#include "TargetMark.h"

TargetMark::TargetMark() :
	GameObject{ "Image/TargetUI/TargetMark.png" },
	hMarkImage_{ INVALID_HANDLE },
	idCounter_{},
	markIdToPosition_{}
{
}

TargetMark::~TargetMark()
{
}

void TargetMark::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());
}

void TargetMark::Update()
{
	const Canvas::Context& CONTEXT{ System().Get<Canvas>().GetContext() };
	UI::LayoutConfig config{};
	CONTEXT.SetRefLayout(&config);


	// 各ポイントの描画
	for (auto& [targetMarkId, position] : markIdToPosition_)
	{
		CONTEXT.DrawImage(hMarkImage_);

		Vector2 screenPos{};

	}
}

void TargetMark::Release()
{
}

TargetMarkId TargetMark::Add(const Vector3& _worldPosition)
{
	TargetMarkId id{ idCounter_++ };
	markIdToPosition_.emplace(id, _worldPosition);

	return id;
}

void TargetMark::SetPosition(const TargetMarkId _id, const Vector3& _worldPosition)
{
	wassert(markIdToPosition_.count(_id) > 0 && "指定Idのマークが存在しない");
	markIdToPosition_[_id] = _worldPosition;
}

void TargetMark::Remove(const TargetMarkId _id)
{
	wassert(markIdToPosition_.count(_id) > 0 && "削除指定Idのマークが存在しない");
	markIdToPosition_.erase(_id);
}

void TargetMark::OnLoadParam(const json& _json)
{
	ResourceSystem& resourceSystem{ System().Get<ResourceSystem>() };

	hMarkImage_ = resourceSystem.LoadTexture(
		SafeGet<std::string>(_json, "ImageFilePath"));
	wassert(hMarkImage_ != INVALID_HANDLE
		&& "マークUIの画像読み込みに失敗");
}
