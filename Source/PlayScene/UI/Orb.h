#pragma once
#include <wtgb.h>


/// <summary>
/// 音符オーブの種類
/// </summary>
enum struct OrbType : size_t
{
	Div4,     // 四分音符
	Div8,     // 八分音符
	Div8x2,   // 八分音符2個分
	Div16x2,  // 16分音符2個分
	Max,      // 最大数
};

/// <summary>
/// 音符オーブの種類数
/// </summary>
constexpr size_t ORB_TYPE_MAX{ static_cast<size_t>(OrbType::Max) };

/// <summary>
/// 音符オーブ
/// </summary>
class Orb : public GameObject
{
public:
	Orb(
		const Vector2Int _position,
		const Vector2Int _target,
		const float _time,
		const OrbType _type);
	~Orb();

	void Init() override;
	void Update() override;
	void Release() override;

	void OnLoad(const json& _json);

private:
	const OrbType type_;  // このオーブの種類

	float scalingTime_;          // 出現するときのフェードイン時間(秒)
	std::string imageFilePath_;  // 画像ファイルパス

	float scalingTimeLeft_;  // 出現するときの大きさフェードイン
	Vector2 imageSize_;      // 画像サイズ
	TextureHandle hImage_;   // 音符画像
	Vector2 position_;       // 描画座標
	Vector2 velocity_;       // 速度
	Vector2 offset_;      // 画像描画のオフセット
};
