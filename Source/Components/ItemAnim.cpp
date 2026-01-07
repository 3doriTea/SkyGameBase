#include "ItemAnim.h"
#include "Systems/CPItemAnim.h"

ItemAnim::ItemAnim() :
	itemType_{},
	totalTime_{},
	timeLeft_{},
	startPos_{},
	endPos_{}
{}

void ItemAnim::Init(wtgb::ViewerCached _system)
{
	timeLeft_ = totalTime_;
}

ItemAnim::~ItemAnim()
{
}
