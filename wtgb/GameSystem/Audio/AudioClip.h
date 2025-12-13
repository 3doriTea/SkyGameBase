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

	private:
		mtbin::BinaryReader* pReader_;  // 読み取りする
		WAVEFORMATEX waveFormat_;  // フォーマット
		std::vector<int8_t> buffer_;  // バッファ
	};
}
