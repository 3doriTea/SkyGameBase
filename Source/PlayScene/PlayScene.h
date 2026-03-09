#pragma once
#include <wtgb.h>
#include "WorldSetting.h"

/// <summary>
/// プレイヤーが坂を降るプレイシーン
/// </summary>
class PlayScene : public GameScene
{
public:
	PlayScene(GameScene::Config&& _config);
	~PlayScene();

	void Start() override;
	void Update() override;

	/// <summary>
	/// ワールドの設定を取得する
	/// </summary>
	/// <returns>ワールドの設定</returns>
	inline WorldConfig GetWorldConfig() const { return worldConfig_; }

	/// <summary>
	/// フィニッシュした！
	/// </summary>
	void Finished();

private:
	WorldConfig worldConfig_;  // ワールドの設定
};
