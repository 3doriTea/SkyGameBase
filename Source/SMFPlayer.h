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

	uint64_t ReadDelta(mtbin::BinaryReader& _br);
private:
	fs::path file_;
};
