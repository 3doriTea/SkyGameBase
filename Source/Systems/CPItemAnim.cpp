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
			return false;  // Ç∑Ç≈Ç…èIóπÇµÇΩÇ»ÇÁñ≥éã
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

		return false;
	});
}
