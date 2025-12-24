#pragma once
#include <wtgb.h>

class TitleNeco : public GameObject
{
	enum IMAGE
	{
		I_HAND,
		I_HANG,
		I_NORM,
		I_MAX,
	};
public:
	TitleNeco(const EntityId _dragCircle);
	~TitleNeco();

	void Init() override;
	void Update() override;
	void Release() override;

	/// <summary>
	/// 移動レートを取得する
	/// </summary>
	/// <returns>移動レート 0.0 .. 1.0</returns>
	float GetMoveRaito() const { return moveRatio_; }

private:
	TextureHandle hImages_[IMAGE::I_MAX];
	float moveRatio_;  // ムーブレート
	bool isDrag_;  // ドラッグ中か

	Vector2Int playButtonShowPos_;  // プレイボタンを表示させるときの位置

	EntityId dragCircle_;  // ドラッグして掴む円
	EntityId playButton_;  // プレイボタン
};
