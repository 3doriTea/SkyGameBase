#pragma once
#include <wtgb.h>


class SMFPlayer : public GameObject
{
public:
	SMFPlayer(const fs::path& _file);
	~SMFPlayer();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	fs::path file_;
};
