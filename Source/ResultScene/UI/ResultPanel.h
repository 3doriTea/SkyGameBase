#pragma once
#include <wtgb.h>
#include "../../GameScore.h"

/// <summary>
/// リザルトシーン動く結果パネル
/// </summary>
class ResultPanel : public GameObject
{
public:
	ResultPanel();
	~ResultPanel();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	void OnLoadParam(const json& _json);

private:
	Vector2Int baseCanvasSize_;       // UI設計時のキャンバスサイズ
	std::string panelImageFile_;      // パネルの画像ファイルパス
	TextureHandle hPanelImage_;       // パネル画像のハンドル
	Vector2Int dragCirclePositionDown_;  // 下がっているときのドラッグ座標
	Vector2Int dragCirclePositionUp_;    // 上がっているときのドラッグ座標
	int dragCircleSizePix_;           // ドラッグ円の直径 pixcel

	EntityId dragPoint_;  // 掴む円のUI
	float animOffsetY_;    // アニメーションで動いたy
	float moveRatio_;      // ムーブレート
	bool isDrag_;          // 掴んでいる true / false
	float toTitleTime_;    // タイトルにシーン遷移する
	std::string numberFontImagePath_;  // 数字のフォント画像パス

	Vector2Int scoreFontSize_;                                // 数字のサイズ
	EntityId numberPlate_[GameScore::ScoreType_Max];          // 数字表示UIのエンティティ
	Vector2Int scoreTextPosition_[GameScore::ScoreType_Max];  // 数字表示UIの座標
};

