#include "PerformanceTester.h"


PerformanceTester::PerformanceTester() :
	frameCounter_{ 0 },
	frameCountPrev_{ 0 },
	timeLeft_{ 1.0f },
	history_{}
{
}

PerformanceTester::~PerformanceTester()
{
}

void PerformanceTester::Update(const float _deltaTime)
{
	// 1秒カウントを減らしていく
	timeLeft_ -= _deltaTime;
	if (timeLeft_ <= 0.0f)
	{
		frameCountPrev_ = frameCounter_;
		// フレームカウントをリセット
		frameCounter_ = 0;
		timeLeft_ = 1.0f;
	}
	else
	{
		frameCounter_++;
	}
}

void PerformanceTester::Stamp(const uint32_t _key)
{
	namespace chrono = std::chrono;

	// スタンプ文字列
	std::string stamp
	{
		std::format(
			"{},{}",
			_key,
			frameCountPrev_)
	};
	history_.push_back(stamp);
}

void PerformanceTester::Dump(const fs::path& _filePath)
{
	std::ofstream ofs{ _filePath };

	wassert(!!ofs && "パフォーマンス計測結果のダンプに失敗: ファイルが開けなかった");

	// 履歴の文字列を出力していく
	for (const std::string& history : history_)
	{
		ofs << history << std::endl;
	}

	ofs.close();
}
