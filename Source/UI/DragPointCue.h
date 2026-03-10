#pragma once
#include <wtgb.h>


/// <summary>
/// ドラッグできる場所を示すUI
/// </summary>
class DragPointCue : public GameObject
{
public:
	DragPointCue(
		const std::string& _imageFilePath,
		const float _animTotalTimeSec,
		const Vector2Int _drawPosition,
		const Vector2Int _drawSize,
		const Vector2Int _baseCanvasSize = Vector2Int::Zero());
	DragPointCue(const std::string& _imageFilePath, const float _animTotalTimeSec);
	~DragPointCue();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	float timeLeft_;             // アニメーションのカウントダウン
	float animTotalTimeSec_;     // 1アニメーションループの秒数
	Vector2Int baseCanvasSize_;  // UI設計時のキャンバスサイズ
	Vector2Int drawPosition_;    // 描画する座標
	Vector2Int drawSize_;        // 描画するサイズ
	std::string imageFilePath_;  // 画像ファイルのパス
	TextureHandle hImage_;       // 円形を示すための画像
};
