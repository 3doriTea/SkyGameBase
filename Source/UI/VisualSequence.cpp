#include "VisualSequence.h"
#include "IVisual.h"

int VisualSequence::INVALID_INDEX_{ -1 };

VisualSequence::VisualSequence() :
	GameObject{ "Simple.json" },
	currentIndex_{ INVALID_INDEX_ },
	visuals_{}
{
}

VisualSequence& VisualSequence::ClearSequence()
{
	currentIndex_ = INVALID_INDEX_;
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
	ShowAt(currentIndex_ + 1);
}

void VisualSequence::ShowAt(const int _index)
{
	if (currentIndex_ <= -1)
	{
		const EntityId EID{ visuals_.at(currentIndex_) };
		IVisual* pVisual{ FindGameObject<IVisual>(EID) };
		pVisual->Hide();
	}

	currentIndex_ = _index;

	if (currentIndex_ < 0 || visuals_.size() <= currentIndex_)
	{
		// ”ÍˆÍŠO‚È‚ç–³Œø‰»
		currentIndex_ = INVALID_INDEX_;
		return;
	}

	const EntityId EID{ visuals_.at(currentIndex_) };
	IVisual* pVisual{ FindGameObject<IVisual>(EID) };
	pVisual->Hide();
}
