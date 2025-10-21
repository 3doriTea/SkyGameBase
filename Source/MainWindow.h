#pragma once
#include "Core/IGameSystem.h"

/// <summary>
/// ゲームのメインウィンドウを司るシステムクラス
/// </summary>
class MainWindow : public wtgb::IGameSystem
{
public:
	MainWindow();
	~MainWindow();

	const CallType GetCallType() override { return CallType::Frame; }

	wtgb::Result Init(const ViewerInit& _viewer) override;

	void Update() override;

	void End() override;
};
