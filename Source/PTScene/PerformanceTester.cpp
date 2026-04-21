#include "PerformanceTester.h"

PerformanceTester::PerformanceTester() :
	frameCounter_{ 0 },
	timeLeft_{ 1.0f },
	history_{}
{
}

PerformanceTester::~PerformanceTester()
{
}

void PerformanceTester::Update(const float _deltaTime)
{
	timeLeft_ -= _deltaTime;
}

void PerformanceTester::Stamp(const std::string_view _desc)
{
	std::chrono::system_clock::time_point nowTime{ std::chrono::system_clock::now() };
	std::string stamp{ std::format("[{}] FPS: {}, {}", /*時間*/, frameCountPrev_, _desc) };
	history_.push_back(stamp);
}

void PerformanceTester::Dump(const fs::path& _filePath)
{
	std::ofstream ofs{ _filePath };

}
