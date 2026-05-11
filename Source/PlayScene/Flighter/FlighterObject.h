#pragma once
#include <wtgb.h>
#include "FlighterFlag.h"


/// <summary>
/// リフトに追従するオブジェクト
/// </summary>
class FlighterObject : public GameObject
{
public:
	FlighterObject(
		const EntityId _flighterController,
		const EntityId _targetChair,
		const EntityId _player,
		const FlighterFlag _flag,
		const ModelHandle _hModel);
	~FlighterObject() {}

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 解放処理
	/// </summary>
	void Release() override;

	/// <summary>
	/// 追従オブジェクトがプレイヤーから離れすぎたかを取得
	/// </summary>
	/// <returns>離れすぎた true / false</returns>
	bool IsRangeOut() const { return isRangeOut_; }

	/// <summary>
	/// 追従を再開する
	/// </summary>
	void ReFollow();

private:
	/// <summary>
	/// パラメータ読み込み
	/// </summary>
	/// <param name="_json">パラメータjson</param>
	void OnLoadParam(const json& _json);

private:
	EntityId flighterController_;   // 追従オブジェクトの管理エンティティ
	EntityId player_;               // 見せつけるプレイヤー
	EntityId targetChair_;          // ターゲットにする椅子
	ModelHandle hModel_;            // モデルのハンドル
	FlighterFlag flag_;             // 飛行フラグ
	bool isRangeOut_;               // 追従オブジェクトがプレイヤーから離れすぎたか
};
