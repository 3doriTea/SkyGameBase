#pragma once
#include <wtgb.h>
#include "Note.h"

/// <summary>
/// SMF を再生する
/// </summary>
class SMFPlayer : public GameObject
{
public:
	using ToneMinMax = std::tuple<uint8_t, uint8_t>;
	using ChannelToToneMinMax = std::map<uint8_t, ToneMinMax>;

	struct Header
	{
		Header() :
			quarterUnit{}
		{}

		uint16_t quarterUnit;  // 四分音符の分解能
	};

	struct Truck
	{
		Truck() :
			name{},
			notes{},
			tempo{},
			toneMax{ 0x00 },
			toneMin{ UINT8_MAX }
		{}

		std::string name;
		std::vector<Note> notes;
		uint32_t tempo;
		uint8_t toneMax;  // 最大の音階
		uint8_t toneMin;  // 最小の音階
	};

	class TruckGenerator
	{
	public:
		TruckGenerator(Truck& _truck, const Header& _header, ChannelToToneMinMax& _channelToToneMinMax_) :
			HEADER_{ _header },
			truck_{ _truck },
			currentTime_{ 0.0f },
			channelToToneMinMax_{ _channelToToneMinMax_ }
		{}
		~TruckGenerator() {}

		void SetName(const std::string& _name);
		void SetTempo(const uint32_t _value);
		/// <summary>
		/// 四分音符の秒数を取得する
		/// </summary>
		/// <returns>四分音符の秒数</returns>
		inline float GetQuarterSec() const { return quarterSec_; }
		void On(const uint8_t _channel, const uint8_t _note, const uint8_t _velocity);
		void Off(const uint8_t _channel, const uint8_t _note, const uint8_t _velocity);

		void AddDeltaTime(const uint64_t _dt);

	private:
		const Header& HEADER_;     // ヘッダへの参照
		static float quarterSec_;  // 四分音符の秒数
		float currentTime_;        // 加算タイマ
		Truck& truck_;             // 作るトラック
		ChannelToToneMinMax& channelToToneMinMax_;
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

	/// <summary>
	/// デルタタイムを取得する
	/// </summary>
	/// <param name="_br">読み取るリーダー</param>
	/// <returns>デルタタイム</returns>
	static uint64_t ReadDelta(mtbin::BinaryReader& _br);

	/// <summary>
	/// ノーツを再生する
	/// </summary>
	/// <param name="_note"></param>
	void PlayTone(const Note& _note);
	/// <summary>
	/// ノーツを再生する
	/// </summary>
	/// <param name="_note">ノーツ</param>
	/// <param name="_hTone">音色の音声ハンドル</param>
	void PlayTone(const Note& _note, const AudioHandle _hTone, const int32_t _offset);

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

	/// <summary>
	/// 再生が終了したか
	/// </summary>
	/// <returns>終了した true / false</returns>
	inline bool IsFinished() const { return playTime_ >= totalPlayTime_; }

	/// <summary>
	/// 四分音符の秒数を取得する
	/// </summary>
	/// <returns>四分音符の秒数</returns>
	inline float GetQuarterSec() const { return quarterSec_; }

	/// <summary>
	/// 再生時間を取得する
	/// </summary>
	/// <returns>再生時間</returns>
	inline float GetPlayTime() const { return playTime_; }

	/// <summary>
	/// トラック情報を取得
	/// </summary>
	/// <param name="_index">トラックインデクス(トラック番号 - 1)</param>
	/// <returns>トラック情報構造体</returns>
	inline Truck& TruckAt(const size_t _index) { return smfTrucks_[_index]; }

	/// <summary>
	/// チャンネルの最小最大トーンを取得する
	/// </summary>
	/// <param name="_channel">チャンネル</param>
	/// <returns>最小最大トーンタプル[toneMin, toneMax]</returns>
	inline ToneMinMax& GetChannelToToneMinMax(const uint8_t _channel) { return channelToToneMinMax_.at(_channel); }

private:
	void OnLoadParam(const json& _json);

private:
	std::function<void(const Note&)> onNoteCallback_;  // ノーツ再生時のイベント
	fs::path file_;                 // smfのパス
	Header smfHeader_;              // smfのヘッダデータ
	std::vector<Truck> smfTrucks_;  // smfのトラックデータ
	// 各チャンネルの最小最大トーン値
	ChannelToToneMinMax channelToToneMinMax_;
	std::vector<size_t> readCurr_;  // 各トラックの再生したノーツインデクス
	float totalPlayTime_;           // 総再生時間
	float quarterSec_;              // 四分音符の秒数

	float playTime_;  // 再生時間
	float playRate_;  // 倍速か
	bool isPlaying_;  // 再生中か

	float playableSampleRateLimit_;  // 再生可能なサンプルレートの最大値

	float toneSampleRateHz_;  // サンプルトーンの周波数

	AudioHandle hTone_;       // 再生する音色
};
