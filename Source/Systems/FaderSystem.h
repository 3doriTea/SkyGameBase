#pragma once
#include "Core/IGameSystem.h"

/// <summary>
/// 画面遷移時のフェードインアウト
/// </summary>
class FaderSystem : public wtgb::IGameSystem
{
public:
	FaderSystem();
	~FaderSystem();

	/// <summary>
	/// 更新の呼び出しタイミング
	/// </summary>
	/// <returns>更新のタイミング</returns>
	const CallType GetCallType() override { return CallType::DoNotUpdate; }

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

	/// <summary>
	/// フェードインフェードアウトする時に表示する画像をセットする
	/// </summary>
	/// <param name="_hImage">画像のハンドル</param>
	void SetImage(const TextureHandle _hImage);

private:
	TextureHandle hImage_;
};
