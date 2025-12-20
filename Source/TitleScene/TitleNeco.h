#pragma once
#include <wtgb.h>

class TitleNeco : public GameObject
{
	enum IMAGE
	{
		I_HAND,
		I_HANG,
		I_NORM,
		I_MAX,
	};
public:
	TitleNeco(const EntityId _dragCircle);
	~TitleNeco();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	TextureHandle hImages_[IMAGE::I_MAX];
	float moveRatio_;  // ムーブレート
	bool isDrag_;  // ドラッグ中か

	EntityId dragCircle_;  // ドラッグして掴む円
};
