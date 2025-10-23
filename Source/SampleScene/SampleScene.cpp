#include "pch\pch.h"
#include "SampleScene.h"

#include "Player.h"

using namespace wtgb;

void SampleScene::Start()
{
	Instantiate<Player>();
}
