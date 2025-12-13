#pragma once
#include "Utility/IResource.h"

namespace wtgb
{
	class AudioClip : public IResource<>
	{
	public:
		AudioClip(mtbin::BinaryReader* _pReader);
		~AudioClip();

		void Init() override;
		void Release() override;

		/// <summary>
		/// 総再生時間を取得する
		/// </summary>
		/// <returns>総再生時間(秒)</returns>
		float GetTotalTimeSec() const;

	private:
		void LoadMp3();

	private:
		mtbin::BinaryReader* pReader_;  // 読み取りする
		WAVEFORMATEX waveFormat_;  // フォーマット
		std::vector<int8_t> buffer_;  // バッファ
	};
}
