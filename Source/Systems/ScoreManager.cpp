#include "ScoreManager.h"

ScoreManager::ScoreManager() :
	currentScore_{ 0 },
	maxScore_{ 0 },
	gameScore_{},
	isFailedGoal_{}
{
}

ScoreManager::~ScoreManager()
{
}

Result ScoreManager::Init(const ViewerInit& _viewer)
{
	return Result::Code::Ok;
}

void ScoreManager::Update(const ViewerUpdate& _system)
{
}

void ScoreManager::End()
{
}

void ScoreManager::ResetGameScore()
{
	gameScore_ = {};
	isFailedGoal_ = false;
}
