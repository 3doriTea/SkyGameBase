#pragma once
#include <wtgb.h>


/// <summary>
/// ヒントUIの基底クラス
/// </summary>
class BaseCue : public GameObject
{
public:
	BaseCue(
		const Vector2Int _position,
		const Vector2Int _canvasSize,
		const fs::path& _imageFile,
		const float _animTimeTotal);
	inline virtual ~BaseCue() {}

	inline virtual void Init() override {}
	void Update() override final;
	inline virtual void Release() override {}

protected:
	/// <summary>
	/// <para>描画処理</para>
	/// <para>継承先でレイアウトの変更をする</para>
	/// </summary>
	/// <param name="_animRatio">アニメーション時間</param>
	/// <param name="_pLayout">描画レイアウト</param>
	virtual void Draw(UI::LayoutConfig* _pLayout, const float _animRatio) = 0;

private:
	TextureHandle hImage_;   // 画像ハンドル
	float animTimeLeft_;     // アニメーションカウントダウン
	float animTimeTotal_;    // アニメーション総再生時間
	Vector2Int position_;    // 描画する座標
	Vector2Int canvasSize_;  // 設計時のキャンバスサイズ
	bool isShow_;            // 表示するか
};
