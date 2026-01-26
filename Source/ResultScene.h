#pragma once
#include <wtgb.h>


/// <summary>
/// 坂を降り終わりスコアの表示を行うリザルトシーン
/// </summary>
class ResultScene : public GameScene
{
public:
	ResultScene();
	~ResultScene();

	void Start() override;
	void Update() override;
};
