#include "BallSphere.h"

BallSphere::BallSphere(const EntityId _targetChara) :
	GameObject{ "Play/BallSphere.json" }
{
	// í«è]Ç∑ÇÈÇΩÇﬂÇ…êeéqä÷åWÇåãÇ‘
	Property().SetParent(_targetChara);
}

BallSphere::~BallSphere()
{
}

void BallSphere::Init()
{
}

void BallSphere::Update()
{
}

void BallSphere::Release()
{
}
