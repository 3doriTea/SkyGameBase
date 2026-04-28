#pragma once
#include <wtgb/wtgb.h>

/// <summary>
/// ゲーム起動時のシーン登録システム
/// </summary>
class FirstSceneRegister : public IGameSystem
{
public:
	FirstSceneRegister() {}
	~FirstSceneRegister() {}

	/// <summary>
	/// 更新タイミングを取得
	/// </summary>
	/// <returns>更新タイミング</returns>
	const CallType GetCallType() override { return CallType::DoNotUpdate; }

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="_viewer">システム参照</param>
	/// <returns>初期化の結果</returns>
	wtgb::Result Init(const ViewerInit& _viewer) override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_system">システム参照</param>
	void Update(const ViewerUpdate& _system) override {}

	/// <summary>
	/// 終了処理
	/// </summary>
	void End() override {}
};
