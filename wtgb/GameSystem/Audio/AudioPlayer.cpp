#include "pch\pch.h"
#include "AudioPlayer.h"
#include "WTGBAssert.h"
#include "../Audio.h"


wtgb::AudioPlayer::AudioPlayer()
{
}

wtgb::AudioPlayer::~AudioPlayer()
{
}

void wtgb::AudioPlayer::Update(const float _dt)
{
	// MEMO: CPUのSleepプロセスを参考にしました。

	if (entryQueue_.size() <= 0)
	{
		return;  // 再生されてないなら回帰
	}

	// 再生終了をデキューする

	auto itr = entryQueue_.begin();
	while (itr != entryQueue_.end())  // 明示的に
	{
		itr->timeLeft -= _dt;

		float diff{ itr->timeLeft };
		if (diff > 0.0f)  // 残り時間がまだある
		{
			break;  // 再生終了していないため離脱
		}
		else  // 残り時間がマイナス
		{
			// 再生終了のため解放
			itr = entryQueue_.erase(itr);

			if (itr == entryQueue_.end())
			{
				break;  // キューが空っぽなら離脱
			}
			itr->timeLeft += diff + _dt;  // マイナスの分を後続に適用
			continue;
		}
	}
}

void wtgb::AudioPlayer::Clear()
{
	entryQueue_.clear();
}

wtgb::SourceVoiceIndex wtgb::AudioPlayer::Play(
	const XAUDIO2_BUFFER& _buffer,
	const WAVEFORMATEX& _format,
	Audio& _audioSystem)
{
	SourceVoiceIndex index{};
	// インデクスを求める
	for (index = 0; index < sourceVoices_.size(); index++)
	{
		if (!useFlag_.at(index))
		{
			break;
		}
	}
	// 全部使われていたら追加する
	if (index == sourceVoices_.size())
	{
		IXAudio2SourceVoice* pSourceVoice{};
		_audioSystem.CreateSourceVoice(&pSourceVoice, _format);
		sourceVoices_.emplace_back(UniqueXAudio2SourceVoice{ pSourceVoice });
	}

	HRESULT hResult{};
	hResult = sourceVoices_.at(index)->SubmitSourceBuffer(&_buffer);

	wassert(SUCCEEDED(hResult) && "音声の登録に失敗");
	if (FAILED(hResult))
	{
		return -1;
	}

	sourceVoices_.at(index)->Start();

	return index;
}

#pragma region AudioEntry

wtgb::AudioPlayer::AudioEntry::AudioEntry(
	AudioPlayer& _audioPlayer,
	const SourceVoiceIndex _sourceVoiceIndex) :
	audioPlayer{ _audioPlayer },
	sourceVoiceIndex{ _sourceVoiceIndex }
{
	_audioPlayer.useFlag_.at(sourceVoiceIndex) = true;
}

wtgb::AudioPlayer::AudioEntry::~AudioEntry()
{
	audioPlayer.useFlag_.at(sourceVoiceIndex) = false;
}

#pragma endregion
