#include "PerformanceReader.h"
#include "PTScene.h"

PerformanceReader::PerformanceReader() :
	GameObject{ "PT/PerformanceReader.json" },
	tester_{}
{
}

PerformanceReader::~PerformanceReader()
{
}

void PerformanceReader::Init()
{
}

void PerformanceReader::Update()
{
	const auto& INPUT{ System().Get<Input>().Getter() };
	const float DT{ System().Get<GameTime>().GetDeltaTime() };

	LOGFLN("DT={}, FPS={}", DT, tester_.GetFPS());

	// フレーム更新
	tester_.Update(DT);

	PTScene* pPTScene{ GetScene<PTScene>() };
	if (pPTScene)
	{
		wassert(pPTScene && "パフォーマンステストシーンの取得に失敗");

		if (INPUT.IsKey(KeyCode::G))
		{
			tester_.Stamp(std::format("SphereCount:{}", pPTScene->GetSphereCount()));
		}
	}

	// Mキーが押されたら計測結果をダンプする
	if (INPUT.IsKeyDown(KeyCode::M))
	{
		tester_.Dump("./Performance.log");
	}
}

void PerformanceReader::Release()
{
}
