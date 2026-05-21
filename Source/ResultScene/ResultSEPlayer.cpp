#include "ResultSEPlayer.h"
#include "../Systems/ScoreManager.h"

ResultSEPlayer::ResultSEPlayer() :
	GameObject{ "Result/ResultSEPlayer.json" },
	hClearSound_{ INVALID_HANDLE },
	hFailedSound_{ INVALID_HANDLE }
{}

ResultSEPlayer::~ResultSEPlayer()
{}

void ResultSEPlayer::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());

	AudioHandle playSound{ INVALID_HANDLE };
	if (System().Get<ScoreManager>().IsFailedGoal())
	{
		// 失敗したなら失敗音を鳴らす
		playSound = hFailedSound_;
	}
	else
	{
		// 成功したなら成功音を鳴らす
		playSound = hClearSound_;
	}

	if (playSound)
	{
		System().Get<Audio>().Play(hClearSound_);
	}
}

void ResultSEPlayer::Update()
{}

void ResultSEPlayer::Release()
{}

void ResultSEPlayer::OnLoadParam(const json& _json)
{
	// 各パラメータを読み込んでいく

	std::string clearSoundFilePath{};
	_json["clearSoundFilePath"].get_to(clearSoundFilePath);
	hClearSound_ = System().Get<Audio>().Load(clearSoundFilePath);


	std::string failedSoundFilePath{};
	_json["failedSoundFilePath"].get_to(clearSoundFilePath);
	//hFailedSound_ = System().Get<Audio>().Load(failedSoundFilePath);
}
