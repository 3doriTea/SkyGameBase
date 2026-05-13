#pragma once
#include <wtgb.h>


/// <summary>
/// フェーダシステムをコントロールする
/// </summary>
class FaderController : public GameObject
{
public:
	FaderController();
	~FaderController();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 解放処理
	/// </summary>
	void Release() override;

	/// <summary>
	/// 幕を開けて表示する
	/// </summary>
	/// <param name="_callback">幕をあげきった時のコールバック関数 void()</param>
	void Show(const std::function<void()>& _callback = []{});

	/// <summary>
	/// 幕を降ろして非表示にする
	/// </summary>
	/// <param name="_callback">幕を降ろしきった時のコールバック関数 void()</param>
	void Hide(const std::function<void()>& _callback = []{});

private:
	/// <summary>
	/// パラメータを読み込む
	/// </summary>
	/// <param name="_json">パラメータjson</param>
	void OnLoadParam(const json& _json);

private:
	TextureHandle hFaderImage_;  // フェーダのハンドル
	float hideTimeSec_;          // 非表示になるまでの時間(秒)
	float showTimeSec_;          // 表示されるまでの時間(秒)
	AlarmHandle hAlarm_;         // フェードインアウト終了時に呼び出されるコールバック
};