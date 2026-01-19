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
	PlayState();
	~PlayState();

	void Init() override;
	void Update() override;
	void Release() override;

	void ChangeState(Type _type);

private:
	std::unique_ptr<IPlayState> pCurrentState_;
};
