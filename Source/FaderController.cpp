#include "FaderController.h"
#include "Systems/FaderSystem.h"

FaderController::FaderController() :
	GameObject{ "FaderController.json" },
	hFaderImage_{ INVALID_HANDLE },
	hideTimeSec_{ 0.0f },
	showTimeSec_{ 0.0f },
	hAlarm_{ INVALID_HANDLE }
{
}

FaderController::~FaderController()
{
}

void FaderController::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());

	FaderSystem& faderSystem{ System().Get<FaderSystem>() };

	faderSystem.SetImage(hFaderImage_);
	faderSystem.SetAlpha(1.0f);
	
	Show();
}

void FaderController::Update()
{
}

void FaderController::Release()
{
}

void FaderController::Show(const std::function<void()>& _callback)
{
	// MEMO: 将来的に中断機能を実装する場合に備えてハンドルを格納
	hAlarm_ = System().Get<Alarm>().Add(_callback, showTimeSec_);
	FaderSystem& faderSystem{ System().Get<FaderSystem>() };
	faderSystem.Out(showTimeSec_);
}

void FaderController::Hide(const std::function<void()>& _callback)
{
	// MEMO: 将来的に中断機能を実装する場合に備えてハンドルを格納
	hAlarm_ = System().Get<Alarm>().Add(_callback, hideTimeSec_);
	FaderSystem& faderSystem{ System().Get<FaderSystem>() };
	faderSystem.In(hideTimeSec_);
}

void FaderController::OnLoadParam(const json& _json)
{
	std::string filePath{};
	_json["FaderImageFile"].get_to(filePath);
	hFaderImage_ = System().Get<ResourceSystem>().LoadTexture(filePath);

	hideTimeSec_ = _json.value("hideTimeSec", 0.5f);
	showTimeSec_ = _json.value("showTimeSec", 0.5f);
}
