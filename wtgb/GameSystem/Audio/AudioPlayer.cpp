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
			//itr->Release();
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
	for (auto& sourceVoice : sourceVoices_)
	{
		if (sourceVoice)
		{
			sourceVoice.get()->Stop();
			sourceVoice.get()->DestroyVoice();
		}
	}
	sourceVoices_.clear();
	useFlag_.clear();
}

wtgb::SourceVoiceIndex wtgb::AudioPlayer::Play(
	const float _playTimeSec,
	const XAUDIO2_BUFFER& _buffer,
	const WAVEFORMATEX& _format,
	Audio& _audioSystem)
{
	SourceVoiceIndex index{};
	// 使われていないインデクスを求める
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
		IXAudio2SourceVoice* pSourceVoice{ nullptr };
		_audioSystem.CreateSourceVoice(&pSourceVoice, _format);
		sourceVoices_.emplace_back(UniqueXAudio2SourceVoice{ pSourceVoice });
		useFlag_.push_back(false);
	}
	else
	{
		IXAudio2SourceVoice* pSourceVoice{ nullptr };
		_audioSystem.CreateSourceVoice(&pSourceVoice, _format);
		if (sourceVoices_.at(index))
		{
			sourceVoices_.at(index).get()->Stop(0);
			sourceVoices_.at(index).get()->FlushSourceBuffers();
			sourceVoices_.at(index).get()->DestroyVoice();
		}

		sourceVoices_.at(index) = std::move(UniqueXAudio2SourceVoice{pSourceVoice});
	}

	HRESULT hResult{};
	hResult = sourceVoices_.at(index)->FlushSourceBuffers();
	wassert(SUCCEEDED(hResult) && "音声バッファの初期化に失敗");
	if (FAILED(hResult))
	{
		return -1;
	}

	hResult = sourceVoices_.at(index)->SubmitSourceBuffer(&_buffer);

	wassert(SUCCEEDED(hResult) && "音声の登録に失敗");
	if (FAILED(hResult))
	{
		return -1;
	}


	sourceVoices_.at(index)->Start();
	InsertEntryQueue(_playTimeSec, index);

	return index;
}

void wtgb::AudioPlayer::InsertEntryQueue(float _timeLeft, const SourceVoiceIndex _index)
{
	float lefter{ _timeLeft };  // 減算用
	float righter{ 0 };         // 加算用

	// 適切な挿入ポイントを見つける
	for (auto itr = entryQueue_.begin(); itr != entryQueue_.end(); itr++)
	{
		if (lefter <= righter + itr->timeLeft)
		{
			_timeLeft = lefter - righter;
			itr = entryQueue_.emplace(itr, _timeLeft, *this, _index);
			itr++;
			itr->timeLeft -= _timeLeft;
			return;
		}
		righter += itr->timeLeft;
	}
	// 見つからなかったら末端に追加
	entryQueue_.emplace_back(_timeLeft, *this, _index);
}

#pragma region AudioEntry

wtgb::AudioPlayer::AudioEntry::AudioEntry(
	const float _timeLeft,
	AudioPlayer& _audioPlayer,
	const SourceVoiceIndex _sourceVoiceIndex) :
	timeLeft{ _timeLeft },
	audioPlayer{ _audioPlayer },
	sourceVoiceIndex{ _sourceVoiceIndex }
{
	_audioPlayer.useFlag_.at(sourceVoiceIndex) = true;
}

wtgb::AudioPlayer::AudioEntry::~AudioEntry()
{
	audioPlayer.useFlag_.at(sourceVoiceIndex) = false;
}

void wtgb::AudioPlayer::AudioEntry::Release()
{
	audioPlayer.useFlag_.at(sourceVoiceIndex) = false;
	audioPlayer.sourceVoices_.at(sourceVoiceIndex).get()->Stop(0);
	audioPlayer.sourceVoices_.at(sourceVoiceIndex).get()->FlushSourceBuffers();
	audioPlayer.sourceVoices_.at(sourceVoiceIndex).get()->DestroyVoice();
}

#pragma endregion
