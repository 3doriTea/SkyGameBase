#include "VisualSequence.h"
#include "IVisual.h"


VisualSequence::VisualSequence() :
	GameObject{ "Simple.json" },
	currentIndex_{ -1 },
	visuals_{}
{
}

VisualSequence& VisualSequence::ClearSequence()
{
	currentIndex_ = -1;
	visuals_.clear();

	return *this;
}

VisualSequence& VisualSequence::AddInSequence(const EntityId _visualEntity)
{
	visuals_.emplace_back(_visualEntity);

	return *this;
}

void VisualSequence::ShowNext()
{
	if (currentIndex_ <= -1)
	{
		const EntityId EID{ visuals_.at(currentIndex_) };
		IVisual* pVisual{ FindGameObject(EID) };
	}
	currentIndex_++;
	if (currentIndex_ >= visuals_.size())
	{
		currentIndex_ = -1;
	}
}

void VisualSequence::ShowAt(const int _index)
{
}
