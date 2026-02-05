#include "GoalGround.h"
#include "State/PlayState.h"


GoalGround::GoalGround(const Vector3& _position) :
	GameObject{ "Play/GoalGround.json" },
	targetName_{},
	target_{ INVALID_ENTITY },
	playStater_{ INVALID_ENTITY }
{
	Transform().SetPosition(_position);
}

GoalGround::~GoalGround()
{
}

void GoalGround::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());

	target_ = FindGameObject(targetName_)->GetEntityId();
	wassert(target_ != INVALID_ENTITY && "ゴールさせるオブジェクトが見つからず");

	playStater_ = FindGameObject("PlayState")->GetEntityId();
	wassert(playStater_ != INVALID_ENTITY && "プレイ状態を管理するオブジェクトが見つからず");
}

void GoalGround::Update()
{
	GameObject* pTargetGameObject{ FindGameObject(target_) };

	// ターゲットが見つかったなら
	if (pTargetGameObject)
	{
		// ひたすらターゲットのx座標で支援する
		Vector3 position{ Transform().GetPosition() };
		Vector3 targetPosition{ pTargetGameObject->Transform().GetPositionWorld() };
		position.x = targetPosition.x;
		Transform().SetPosition(position);

		if (targetPosition.z > position.z)
		{
			// ターゲットがゴールの中心座標を超えた！！！　語――――ル
			PlayState* pPlayState{ FindGameObject<PlayState>(playStater_) };
			pPlayState->ChangeState(PlayState::Type::Finished);
		}
	}
}

void GoalGround::Release()
{
}

void GoalGround::OnLoadParam(const json& _json)
{
	targetName_ = _json.value("targetName", "");
}
