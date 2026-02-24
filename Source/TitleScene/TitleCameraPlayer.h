#pragma once
#include <wtgb.h>


/// <summary>
/// タイトルシーンのカメラ設定
/// </summary>
class TitleCameraPlayer : public GameObject
{
public:
	TitleCameraPlayer();
	~TitleCameraPlayer();

	void Init() override;
	void Update() override;

private:

};
