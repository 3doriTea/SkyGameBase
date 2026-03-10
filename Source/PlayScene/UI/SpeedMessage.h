#pragma once
#include <wtgb.h>

/// <summary>
/// プレイヤーの速度に応じて表示するメッセージUI
/// </summary>
class SpeedMessage : public GameObject
{
public:
	SpeedMessage(const EntityId _player);
	~SpeedMessage();

	void OnLoadParam(const json& _json);
	void Init() override;
	void Update() override;
	void Release() override;

private:
	TextureHandle hTextureTooFast_;  // 速すぎメッセージテクスチャハンドラ
	TextureHandle hTextureTooSlow_;  // 遅すぎメッセージテクスチャハンドラ

	fs::path imageFileTooFast_;  // 速すぎメッセージ画像ファイル
	fs::path imageFileTooSlow_;  // 遅すぎメッセージ画像ファイル

	EntityId speedController_;  // スピードを取得するプレイヤーエンティティ

	Vector2Int imageSize_;  // 画像サイズ
};
