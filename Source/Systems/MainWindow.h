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

	/// <summary>
	/// 更新の呼び出しタイミング
	/// </summary>
	/// <returns>更新のタイミング</returns>
	const CallType GetCallType() override { return CallType::Frame; }

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="_viewer">システムの参照</param>
	/// <returns>初期化処理の結果</returns>
	wtgb::Result Init(const ViewerInit& _viewer) override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_system">システムの参照</param>
	void Update(const ViewerUpdate& _system) override;

	/// <summary>
	/// 終了処理
	/// </summary>
	void End() override;
};
