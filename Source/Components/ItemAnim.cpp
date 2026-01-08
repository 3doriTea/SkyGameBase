#include "ItemAnim.h"
#include "Systems/CPItemAnim.h"

ItemAnim::ItemAnim() :
	itemType_{},
	totalTime_{},
	timerUp_{ 0.0f },
	startPos_{},
	endPos_{},
	isFinished_{ false }
{}

void ItemAnim::Init(wtgb::ViewerCached _system)
{
}

ItemAnim::~ItemAnim()
{
}
