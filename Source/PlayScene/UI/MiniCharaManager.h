#pragma once
#include <wtgb.h>
#include "../CloudLevel.h"


/// <summary>
/// ミニキャラの統一を図る
/// </summary>
class MiniCharaManager : public GameObject
{
public:
	MiniCharaManager(const EntityId _smfPlayer);
	~MiniCharaManager();

	void Init() override;
	void Update() override;
	void Release() override;

	/// <summary>
	/// レベルアップしたときに呼び出してほしい処理
	/// </summary>
	/// <param name="_current">現在のレベル</param>
	void LevelUp(const CloudLevel _current);
	/// <summary>
	/// レベルダウンしたときに呼び出してほしい処理
	/// </summary>
	/// <param name="_current">現在のレベル</param>
	void LevelDown(const CloudLevel _current);

private:
	void OnLoad(const json& _json);
	/// <summary>
	/// 最高レベルを更新したか
	/// </summary>
	/// <returns>更新した true / false</returns>
	bool TryUpdateMaxLevel();

private:
	EntityId smfPlayer_;       // smf再生するやつ

	CloudLevel currentLevel_;  // 現在の演奏レベル
	CloudLevel maxLevel_;      // 到達した最高の演奏レベル
	std::vector<EntityId> miniCharars_;  // 登場しているミニキャラたち

	Vector2Int imageSize_;  // ミニキャラの画像サイズ
	float iamgeScale_;      // ミニキャラの拡縮
};
