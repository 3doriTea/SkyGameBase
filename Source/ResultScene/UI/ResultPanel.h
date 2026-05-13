#pragma once
#include <wtgb.h>
#include "../../GameScore.h"

/// <summary>
/// リザルトシーン動く結果パネル
/// </summary>
class ResultPanel : public GameObject
{
public:
	ResultPanel(const EntityId _faderController);
	~ResultPanel();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	void OnLoadParam(const json& _json);

private:
	EntityId faderController_;

	Vector2Int baseCanvasSize_;          // UI設計時のキャンバスサイズ
	std::string panelImageFileResult_;   // パネルの画像ファイルパス
	std::string panelImageFileFailed_;   // パネルの画像ファイルパス
	std::string panelImageFileWarning_;  // パネルの画像ファイルパス
	TextureHandle hPanelImage_;          // パネル画像のハンドル
	Vector2Int dragCirclePositionDown_;  // 下がっているときのドラッグ座標
	Vector2Int dragCirclePositionUp_;    // 上がっているときのドラッグ座標
	int dragCircleSizePix_;              // ドラッグ円の直径 pixcel

	EntityId dragPoint_;               // 掴む円のUI
	float animOffsetY_;                // アニメーションで動いたy
	float moveRatio_;                  // ムーブレート
	bool isDrag_;                      // 掴んでいる true / false
	float toTitleTime_;                // タイトルにシーン遷移する
	std::string numberFontImagePath_;  // 数字のフォント画像パス

	bool isShowResult_;  // 結果を表示するか

	Vector2Int scoreFontSize_;                                // 数字のサイズ
	EntityId stringPlate_[GameScore::ScoreType_Max];          // 数字表示UIのエンティティ
	Vector2Int scoreTextPosition_[GameScore::ScoreType_Max];  // 数字表示UIの座標
};

