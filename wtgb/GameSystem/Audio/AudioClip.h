#pragma once
#include "Utility/IResource.h"

namespace wtgb
{
	class AudioClip : public IResource<>
	{
	public:
		AudioClip(mtbin::BinaryReader* _pReader, const std::string& _name);
		~AudioClip();

		void Init() override;
		void Release() override;

		/// <summary>
		/// 総再生時間を取得する
		/// </summary>
		/// <returns>総再生時間(秒)</returns>
		float GetTotalTimeSec() const;
		/// <summary>
		/// 総再生時間を取得する
		/// </summary>
		/// <returns>総再生時間(秒)</returns>
		//static float GetTotalTimeSec(const WAVEFORMATEX& _format);

		inline size_t GetBufferSize() const { return buffer_.size(); }
		inline const int8_t* GetBufferData() const { return buffer_.data(); }
		/// <summary>
		/// 名前を取得
		/// </summary>
		/// <returns>識別名</returns>
		inline std::string_view GetName() const { return name_; }

		WAVEFORMATEX GetFormat() const { return waveFormat_; }

	private:
		void LoadMp3();

	private:
		std::string name_;  // 識別名

		mtbin::BinaryReader* pReader_;  // 読み取りする
		WAVEFORMATEX waveFormat_;  // フォーマット
		std::vector<int8_t> buffer_;  // バッファ
	};
}
