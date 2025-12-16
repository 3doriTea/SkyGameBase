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

	class TruckGenerater
	{
	public:
		TruckGenerater(Truck& _truck, const Header& _header) :
			HEADER_{ _header },
			truck_{ _truck },
			currentTime_{ 0.0f }
		{}
		~TruckGenerater() {}

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
	void OnNote(const std::function<void(const Note&)> _callback);

	void Init() override;
	void Update() override;
	void Release() override;

	uint64_t ReadDelta(mtbin::BinaryReader& _br);

	/// <summary>
	/// ノーツを再生する
	/// </summary>
	/// <param name="_note"></param>
	void PlayTone(const Note& _note);

private:
	std::function<void(const Note&)> onNoteCallback_;
	fs::path file_;
	Header smfHeader_;  // smfのヘッダデータ
	std::vector<Truck> smfTrucks_;  // smfのトラックデータ
	float playTime_;  // 再生時間
	std::vector<size_t> readCurr_;

	float toneSampleRateHz_;  // サンプルトーンの周波数
	AudioHandle hTone_[1];
};
