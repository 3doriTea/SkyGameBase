#pragma once
#include <wtgb.h>


class SMFPlayer : public GameObject
{
public:
	struct Note
	{
		Note() :
			Note{ 0.0f, 0, 0, 0 }
		{}
		Note(
			float _totalTime,
			uint8_t _channel,
			uint8_t _noteNumber,
			uint8_t _velocity) :
			totalTime{ _totalTime },
			channel{ _channel },
			noteNumber{ _noteNumber },
			velocity{ _velocity }
		{}
		float totalTime;     // 絶対的な時間
		//float diffTime;    // 前回のノーツとの相対的な時間
		uint8_t channel;     // チャンネル
		uint8_t noteNumber;  // 音の高さ
		uint8_t velocity;    // 音の強さ
	};
	
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

	class TruckGenerater
	{
	public:
		TruckGenerater(Truck& _truck, const Header& _header) :
			HEADER_{ _header },
			truck_{ _truck },
			prevTime_{ 0.0f },
			dtSum_{ 0.0f }
		{}
		~TruckGenerater() {}

		void SetName(const std::string& _name);
		void SetTempo(const uint32_t _value);
		void On(const uint8_t _channel, const uint8_t _note, const uint8_t _velocity);

		void AddDeltaTime(const uint64_t _dt);

	private:
		const Header& HEADER_;  // ヘッダへの参照
		static float quarterSec_;      // 四分音符の秒数
		float dtSum_;            // デルタタイムの合計
		float prevTime_;           // 前の加算タイマ
		Truck& truck_;          // 作るトラック
	};

public:
	SMFPlayer(const fs::path& _file);
	~SMFPlayer();

	void Init() override;
	void Update() override;
	void Release() override;

	uint64_t ReadDelta(mtbin::BinaryReader& _br);
private:
	fs::path file_;
	Header smfHeader_;  // smfのヘッダデータ
	std::vector<Truck> smfTrucks_;  // smfのトラックデータ
	float playTime_;  // 再生時間
	std::vector<size_t> readCurr_;

	float toneSampleRateHz_;  // サンプルトーンの周波数
	AudioHandle hTone_[1];
};
