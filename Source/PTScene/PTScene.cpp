#include "PTScene.h"
#include "SimplePlane.h"
#include "SimpleSphere.h"
#include "SimpleCamera.h"
#include "PerformanceReader.h"

PTScene::PTScene(GameScene::Config&& _config) :
	GameScene{ std::move(_config) },
	animationTime_{},
	sphereCount_{ 0 }
{
}

PTScene::~PTScene()
{
}

void PTScene::Start()
{
	Instantiate<SimplePlane>();
	Instantiate<SimpleCamera>();
	Instantiate<PerformanceReader>();
}

void PTScene::Update()
{
	const auto& input{ System().Get<Input>().Getter() };
	
	// スペースキーが押されたら球体をインスタンス
	if (input.IsKey(KeyCode::G))
	{
		for (int i = 0; i < 30; i++)
		{
			Instantiate<SimpleSphere>(GetInstancePositionSphere());
			sphereCount_++;
		}
	}
}

Vector3 PTScene::GetInstancePositionSphere()
{
	using namespace DirectX;

	static float angle{ 0.0f };
	static float distance{ 0.0f };
	static int countMax{ 0 };
	static const int ADD_COUNT{ 4 };
	static const float ADD_DISTANCE{ 2.0f };

	angle += XM_2PI / countMax;
	if ((angle + FLT_EPSILON) >= XM_2PI)
	{
		angle = 0.0f;
		distance += ADD_DISTANCE;
		countMax += ADD_COUNT;
	}
	Vector3 position{};

	// 円形に広がる
	position.x = std::sinf(angle) * distance;
	position.y = std::cosf(angle) * distance;

	return position;
}
