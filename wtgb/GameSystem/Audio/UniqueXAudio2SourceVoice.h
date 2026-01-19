#pragma once
#include "pch/pch.h"
#include <memory>

namespace wtgb
{
	/// <summary>
	/// 解放時の処理
	/// </summary>
	struct XAudio2SourceVoiceDeleter
	{
		void operator()(IXAudio2SourceVoice* _p) const
		{
			if (_p != nullptr)
			{
				_p->Stop(0);
				_p->FlushSourceBuffers();
				_p->DestroyVoice();
			}
		}
	};

	/// <summary>
	/// IXAudio2SouceVoiceユニークポインタ
	/// </summary>
	using UniqueXAudio2SourceVoice = std::unique_ptr<IXAudio2SourceVoice, XAudio2SourceVoiceDeleter>;
}
