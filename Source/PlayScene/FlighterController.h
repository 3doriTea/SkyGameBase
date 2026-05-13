#pragma once
#include <wtgb.h>
#include "Flighter/FlighterFlag.h"


/// <summary>
/// リフトに追従するオブジェクトを管理
/// </summary>
class FlighterController : public GameObject
{
private:
	struct VFormationPosition
	{
		float x;
		float z;
	};

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
	/// <summary>
	/// パラメータを読み込む
	/// </summary>
	/// <param name="_json">パラメータJSON</param>
	void OnLoadParam(const json& _json);

	/// <summary>
	/// 渡り鳥の逆V字編隊の座標を取得
	/// </summary>
	/// <param name="_index">インデクス</param>
	/// <returns>y座標 z座標</returns>
	VFormationPosition GetVFormationPosition(const uint32_t _index) const;

private:
	EntityId liftStructure_;                   // リフト本体
	EntityId player_;                          // プレイヤー
	ModelHandle hModel_;                       // モデルのハンドル
	uint32_t flighterCount_;                   // 追従オブジェクトの総数
	float findChairForwardOffset_;             // 追従オブジェクト検索の前方向オフセット
	std::vector<FlighterFlag> flighterFlags_;  // 追従オブジェクトのフラグ
	std::vector<EntityId> flighterEntities_;   // 追従オブジェクトのエンティティ
	float vFormationDistanceX_;                 // v字編隊を組む時の距離 x
	float vFormationDistanceZ_;                 // v字編隊を組む時の距離 z
};
