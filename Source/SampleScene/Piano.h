#pragma once
#include <wtgb.h>

class Piano : public GameObject
{
public:
	Piano();
	~Piano();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	AudioHandle hTestAudio_;
};
