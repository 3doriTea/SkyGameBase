#include "CPItemAnim.h"
#include "GameSystem/GameTime.h"
#include "GameSystem/CPGameObject.h"
#include "GameSystem/CPTransform.h"
#include "Utility/Mathf.h"
#include "Utility/Ease.h"

using namespace wtgb;

CPItemAnim::CPItemAnim()
{
}

CPItemAnim::~CPItemAnim()
{
}

void CPItemAnim::Init()
{
}

void CPItemAnim::Update()
{
	CPTransform& cpTransform{ System().Get<CPTransform>()};
	CPGameObject& cpGameObject{ System().Get<CPGameObject>() };
	float dt = System().Get<GameTime>().GetDeltaTime();

	ForEach([dt, &cpTransform, &cpGameObject](ItemAnim& _itemAnim, size_t _index) -> BreakToken
	{
		if (_itemAnim.isFinished_)
		{
			return false;  // ‚·‚Å‚ÉI—¹‚µ‚½‚È‚ç–³Ž‹
		}

		_itemAnim.timerUp_ += dt;
		if (_itemAnim.timerUp_ >= _itemAnim.totalTime_)
		{
			_itemAnim.timerUp_ = _itemAnim.totalTime_;
			_itemAnim.isFinished_ = true;
		}

		EntityId entity{ cpGameObject.GetEntityId(_index) };
		Transform* pTransform{ cpTransform.Get(entity) };

		Vector3 pos{ Mathf::Lerp(_itemAnim.startPos_, _itemAnim.endPos_, Ease::OutElastic(_itemAnim.GetRatio())) };
		pTransform->SetPosition(pos);

		return false;
	});
}
