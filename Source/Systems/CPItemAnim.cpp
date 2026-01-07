#include "CPItemAnim.h"
#include "GameSystem/GameTime.h"
#include "GameSystem/CPGameObject.h"
#include "GameSystem/CPTransform.h"
#include "Utility/Mathf.h"

using namespace wtgb;

CPItemAnim::CPItemAnim()
{
}

CPItemAnim::~CPItemAnim()
{
}

Result CPItemAnim::Init(const ViewerInit& _viewer)
{
	return Result::Code::Ok;
}

void CPItemAnim::Update(const ViewerUpdate& _system)
{
	CPTransform& cpTransform{_system.Get<CPTransform>() };
	CPGameObject& cpGameObject{ _system.Get<CPGameObject>() };
	float dt = _system.Get<GameTime>().GetDeltaTime();

	ForEach([dt, &cpTransform, &cpGameObject](ItemAnim& _itemAnim, size_t _index) -> BreakToken
	{
		if (_itemAnim.isFinished_)
		{
			return;  // Ç∑Ç≈Ç…èIóπÇµÇΩÇ»ÇÁñ≥éã
		}

		_itemAnim.timeLeft_ -= dt;
		if (_itemAnim.timeLeft_ <= 0.0f)
		{
			_itemAnim.timeLeft_ = 0.0f;
			_itemAnim.isFinished_ = true;
		}

		EntityId entity{ cpGameObject.GetEntityId(_index) };
		Transform* pTransform{ cpTransform.Get(entity) };

		Vector3 pos{ Mathf::Lerp(_itemAnim.startPos_, _itemAnim.endPos_, _itemAnim.GetRatio()) };
		pTransform->SetPosition(pos);
	});
}

void CPItemAnim::End()
{
}

CPItemAnim::~CPItemAnim()
{
}
