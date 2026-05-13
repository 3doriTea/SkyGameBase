#pragma once
#include <wtgb.h>
//#include <Core/IGameSystem.h>
//#include <CoreType/Handler.h>

/// <summary>
/// 画面遷移時のフェードインアウト
/// </summary>
class FaderSystem : public wtgb::IGameSystem
{
	enum struct FadeType
	{
		Stop,     // 動かさない
		FadeIn,   // フェードイン 隠す
		FadeOut,  // フェードアウト 表示
	};

public:
	FaderSystem();
	~FaderSystem();

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

	/// <summary>
	/// フェードインフェードアウトする時に表示する画像をセットする
	/// </summary>
	/// <param name="_hImage">画像のハンドル</param>
	void SetImage(const TextureHandle _hImage);

	/// <summary>
	/// フェードインして隠す
	/// </summary>
	/// <param name="_timeSec">フェードインする時間</param>
	void In(const float _timeSec);

	/// <summary>
	/// フェードアウトして表示する
	/// </summary>
	/// <param name="_timeSec">フェードアウトする時間</param>
	void Out(const float _timeSec);

	/// <summary>
	/// フェーダの透明度をセットする
	/// </summary>
	/// <param name="_alpha">透明度 0.0 .. 1.0</param>
	void SetAlpha(const float _alpha);

private:
	TextureHandle hImage_;  // 画像ハンドル
	float alpha_;           // 透明度
	float timeLeft_;        // 残り時間
	float maxTimeSec_;      // フェードインアウトする総時間
	FadeType fadeType_;     // フェードの方向
};
