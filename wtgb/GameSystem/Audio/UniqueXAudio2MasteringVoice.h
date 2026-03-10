#pragma once
#include "pch/pch.h"
#include <memory>

namespace wtgb
{
	/// <summary>
	/// 解放時の処理
	/// </summary>
	struct XAudio2MasteringVoiceDeleter
	{
		void operator()(IXAudio2MasteringVoice* _p) const
		{
			if (_p != nullptr)
			{
				_p->DestroyVoice();
			}
		}
	};

	/// <summary>
	/// IXAudio2SouceVoiceユニークポインタ
	/// </summary>
	using UniqueXAudio2MasteringVoice = std::unique_ptr<IXAudio2MasteringVoice, XAudio2MasteringVoiceDeleter>;
}
