#pragma once
#include <wtgb.h>


/// <summary>
/// リフトに追従するオブジェクトを管理
/// </summary>
class FlighterController : public GameObject
{
public:
	FlighterController(const EntityId _liftStructure, const EntityId _player);
	~FlighterController();

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

private:
	void OnLoadParam(const json& _json);

private:
	EntityId liftStructure_;  // リフト本体
	EntityId player_;         // プレイヤー
	ModelHandle hModel_;      // モデルのハンドル
};
