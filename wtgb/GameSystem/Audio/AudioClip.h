#pragma once
#include "Utility/IResource.h"

namespace wtgb
{
	class AudioClip : public IResource<>
	{
	public:
		AudioClip(const fs::path& _filePath);
		~AudioClip();

		void Init() override;
		void Release() override;

	private:
		fs::path filePath_;  // ファイルパス
		WAVEFORMATEX waveFormat_;  // フォーマット
		std::vector<int8_t> buffer_;  // バッファ
	};
}
