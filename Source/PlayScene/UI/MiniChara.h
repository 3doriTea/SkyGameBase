#pragma once
#include <wtgb.h>


/// <summary>
/// 演奏レベルが上がるごとに増えるミニキャラ
/// </summary>
class MiniChara : public GameObject
{
public:
	MiniChara(const EntityId _dropCloud, const EntityId _smfPlayer);
	~MiniChara();

	void OnLoadParam(const json& _json);
	void Init() override;
	void Update() override;
	void Release() override {}

private:
	TextureHandle hImage_;  // キャラの画像
	EntityId dropCloud_;    // 雲
	EntityId smfPlayer_;    // smf player

	Vector2Int imageSize_;
	float scale_;          // 画像のスケール
	float totalAnimTime_;  // アニメーション総時間
	float animTimeLeft_;   // アニメーションタイマー
};
