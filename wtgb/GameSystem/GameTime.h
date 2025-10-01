#pragma once
#include "Core/IGameSystem.h"

// LARGE_INTEGER の前方宣言
typedef union _LARGE_INTEGER LARGE_INTEGER;


namespace wtgb
{
	class GameTime
	{
	public:
		GameTime();
		~GameTime();

		const float DeltaTime() const { return deltaTimeSec_ }

	private:
		float deltaTimeSec_;  // フレーム間時間
		LARGE_INTEGER currentMicro_;  // 現在のCPU時間 (マイクロ秒)
		LARGE_INTEGER previousMicro_;  // 前回のCPU時間 (マイクロ秒)
	};
}
