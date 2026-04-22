#pragma once
#include <wtgb.h>

/// <summary>
/// 計測用シンプルな土台
/// </summary>
class SimplePlane : public GameObject
{
public:
	SimplePlane();
	~SimplePlane();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 解放処理
	/// </summary>
	void Release() override;
};
