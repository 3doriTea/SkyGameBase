#pragma once
#include <wtgb.h>
#include "Note.h"


class SMFPlayer : public GameObject
{
public:
	struct Header
	{
		Header() :
			quaterUnit{}
		{}

		uint16_t quaterUnit;  // 四分音符の分解能
	};

	struct Truck
	{
		Truck() :
			name{},
			notes{},
			tempo{}
		{}

		std::string name;
		std::vector<Note> notes;
		uint32_t tempo;
	};

	class TruckGenerator
	{
	public:
		TruckGenerator(Truck& _truck, const Header& _header) :
			HEADER_{ _header },
			truck_{ _truck },
			currentTime_{ 0.0f }
		{}
		~TruckGenerator() {}

		void SetName(const std::string& _name);
		void SetTempo(const uint32_t _value);
		void On(const uint8_t _channel, const uint8_t _note, const uint8_t _velocity);
		void Off(const uint8_t _channel, const uint8_t _note, const uint8_t _velocity);

		void AddDeltaTime(const uint64_t _dt);

	private:
		const Header& HEADER_;  // ヘッダへの参照
		static float quarterSec_;      // 四分音符の秒数
		float currentTime_;           // 加算タイマ
		Truck& truck_;          // 作るトラック
	};

public:
	SMFPlayer(const fs::path& _file);
	~SMFPlayer();

	/// <summary>
	/// ノーツが来たときの処理
	/// </summary>
	/// <param name="_callback"></param>
	void OnNote(const std::function<void(Note)> _callback);

	void Init() override;
	void Update() override;
	void Release() override;

	uint64_t ReadDelta(mtbin::BinaryReader& _br);

	/// <summary>
	/// ノーツを再生する
	/// </summary>
	/// <param name="_note"></param>
	void PlayTone(const Note& _note);

	/// <summary>
	/// 再生する
	/// </summary>
	inline void Play() { isPlaying_ = true; }
	/// <summary>
	/// 停止する
	/// </summary>
	inline void Stop() { isPlaying_ = false; }
	
	/// <summary>
	/// 再生倍率をセットする
	/// </summary>
	/// <param name="_rate">再生倍率(0.0 .. 1.0 ..)</param>
	inline void SetPlayRate(const float _rate) { playRate_ = _rate; }

	/// <summary>
	/// 再生する音色音源をセットする
	/// </summary>
	/// <param name="_hAudio">音色となる音源</param>
	void SetToneAudioHandle(const AudioHandle _hAudio);

private:
	std::function<void(const Note&)> onNoteCallback_;
	fs::path file_;
	Header smfHeader_;  // smfのヘッダデータ
	std::vector<Truck> smfTrucks_;  // smfのトラックデータ
	std::vector<size_t> readCurr_;

	float playTime_;  // 再生時間
	float playRate_;  // 倍速か
	bool isPlaying_;  // 再生中か

	float toneSampleRateHz_;  // サンプルトーンの周波数

	AudioHandle hTone_;       // 再生する音色
};
