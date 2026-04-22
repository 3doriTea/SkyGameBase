#pragma once
#include <wtgb.h>

/// <summary>
/// シンプルな球体オブジェクト
/// </summary>
class SimpleSphere : public GameObject
{
public:
	SimpleSphere(const Vector3 _position);
	~SimpleSphere();

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
