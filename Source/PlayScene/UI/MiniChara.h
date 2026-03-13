#pragma once
#include <wtgb.h>
#include "MiniChara/IMiniCharaState.h"


enum struct MiniCharaType
{
	Base3,
	Tubar,
	Monkitty,
	Glocken,
};

/// <summary>
/// 演奏レベルが上がるごとに増えるミニキャラ
/// </summary>
class MiniChara : public GameObject
{
	friend class MiniCharaMonkitty;
	friend class MiniCharaBase3;
	friend class MiniCharaTubar;
	friend class MiniCharaGlocken;
public:
	struct Config
	{
		Config(
			float _moveTime,
			float _totalAnimTime,
			MiniCharaType _type) :
			moveTime{ _moveTime },
			totalAnimTime{ _totalAnimTime },
			type{ _type }
		{}
		float moveTime;       // 目的地までの移動時間
		float totalAnimTime;  // アニメーション総時間
		MiniCharaType type;   // ミニキャラの種類
	};

public:
	MiniChara(const EntityId _miniCharaManager, const Config& _config);
	~MiniChara();

	void OnLoadParam(const json& _json);
	void Init() override;
	void Update() override;
	void Release() override {}

	void MoveAt(const Vector2Int _position);

private:
	std::unique_ptr<IMiniCharaState> pMiniCharaState_;  // ミニキャラステート
	TextureHandle hImage_;  // キャラの画像
	EntityId manager_;      // ミニキャラ統括

	Vector2Int imageSize_;
	float scale_;          // 画像のスケール
	float animTimeLeft_;   // アニメーションタイマー

	Vector2Int drawPosition_;  // 描画座標

	float moveTimeLeft_;    // 移動時のタイマー
	Vector2Int targetPos_;  // 移動先の座標
	Vector2Int fromPos_;     // 移動元の座標

	Config config_;  // 設定
};
