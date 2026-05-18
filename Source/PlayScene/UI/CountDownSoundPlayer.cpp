#include "CountDownSoundPlayer.h"

CountDownSoundPlayer::CountDownSoundPlayer() :
	GameObject{ "Play/CountDownSoundPlayer.json" },
	hSoundHigh_{ INVALID_HANDLE },
	hSoundLow_{ INVALID_HANDLE }
{
}

CountDownSoundPlayer::~CountDownSoundPlayer()
{
}

void CountDownSoundPlayer::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());

	// 予めカウントダウン値の秒部分を代入しておく
	prevTimeLeftSec_ = static_cast<int>(timeLeft_);
}

void CountDownSoundPlayer::Update()
{
	const float DT{ System().Get<GameTime>().GetDeltaTime() };
	timeLeft_ -= DT;

	// 現在の秒部分
	int cuurentTimeLeftSec{ static_cast<int>(timeLeft_) };

	// 不一致ならカウントダウン1秒間が進んだ
	if (prevTimeLeftSec_ != cuurentTimeLeftSec)
	{
		prevTimeLeftSec_ = cuurentTimeLeftSec;

		int hPlayAudio{ INVALID_HANDLE };

		if (prevTimeLeftSec_ == 0)
		{
			hPlayAudio = hSoundHigh_;
			DestroyMe();
		}
		else
		{
			hPlayAudio = hSoundLow_;
		}

		System().Get<Audio>().Play(hPlayAudio);
	}
}

void CountDownSoundPlayer::Release()
{
}

void CountDownSoundPlayer::OnLoadParam(const json& _json)
{
	std::string soundHighFilePath{};
	_json["SoundHighFilePath"].get_to(soundHighFilePath);

	hSoundHigh_ = System().Get<Audio>().Load(soundHighFilePath);

	std::string soundLowFilePath{};
	_json["SoundLowFilePath"].get_to(soundLowFilePath);
	
	hSoundLow_ = System().Get<Audio>().Load(soundLowFilePath);

	// カウントダウンタイムを取得する
	timeLeft_ = _json.value("timeLeft", 4.0f);
}
