#pragma once
#include <wtgb.h>

/// <summary>
/// <para>プレイシーン内での状態管理クラス</para>
/// <para>案内UI等に影響</para>
/// </summary>
class PlayState : public GameObject
{
public:
	enum struct Type
	{
		StartLine,  // 頂上にいる
		Falling,    // 下山中
		Finished,   // 下山終了
	};

private:
	struct IPlayState
	{
		virtual ~IPlayState() = default;
		virtual Type GetType() = 0;
		virtual void Update(ViewerCached _system) = 0;
	};

	struct StartLine : IPlayState
	{
		inline Type GetType() override { return Type::StartLine; }
		void Update(ViewerCached _system) override;
	};

	struct Falling : IPlayState
	{
		inline Type GetType() override { return Type::Falling; }
		void Update(ViewerCached _system) override;
	};

	struct Finished : IPlayState
	{
		inline Type GetType() override { return Type::Finished; }
		void Update(ViewerCached _system) override;
	};

public:
	using ToUnregisterFlag = bool;
	using OnChangedCallback = std::function<ToUnregisterFlag(Type)>;

	PlayState();
	~PlayState();

	void Init() override;
	void Update() override;
	void Release() override;

	/// <summary>
	/// 状態変更があったときのコールバック処理
	/// </summary>
	/// <param name="_callback">(次の状態) -> 登録解除するかのフラグtrue / false</param>
	void OnChanged(OnChangedCallback&& _callback);

	/// <summary>
	/// 状態をチェンジする
	/// </summary>
	/// <param name="_type">次の状態</param>
	void ChangeState(Type _type);
	/// <summary>
	/// 現在の状態を取得する
	/// </summary>
	/// <returns></returns>
	Type GetState() const;

private:
	// 変更時のイベント
	std::list<OnChangedCallback> onChangedEvents_;
	std::unique_ptr<IPlayState> pCurrentState_;
};
