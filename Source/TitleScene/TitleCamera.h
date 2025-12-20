#pragma once
#include <wtgb.h>

class TitleCamera : public GameObject
{
public:
	TitleCamera(const EntityId _titleNeco);
	~TitleCamera();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	EntityId titleNeco_;
};
