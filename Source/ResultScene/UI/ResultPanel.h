#pragma once
#include <wtgb.h>

/// <summary>
/// リザルトシーン動く結果パネル
/// </summary>
class ResultPanel : public GameObject
{
public:
	ResultPanel(const EntityId _dragCircle);
	~ResultPanel();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	void OnLoadParam(const json& _json);

private:
	Vector2Int baseCanvasSize_;     // UI設計時のキャンバスサイズ
	std::string panelImageFile_;    // パネルの画像ファイルパス
	TextureHandle hPanelImage_;     // パネル画像のハンドル

	EntityId dragCircle_;             // 掴む円のUI
	float animOffsetY_;               // アニメーションで動いたy
	float moveRatio_;                 // ムーブレート
	bool isDrag_;                     // 掴んでいる true / false
	Vector2 dragCirclePositionDown_;  // 下がっているときのドラッグ座標
	Vector2 dragCirclePositionUp_;    // 上がっているときのドラッグ座標
};

