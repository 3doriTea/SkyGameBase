#pragma once
#include <wtgb.h>

/// <summary>
/// ’Pƒ‚É‹È‚ğ—¬‚·
/// </summary>
class MusicPlayer : public GameObject
{
public:
	MusicPlayer();
	~MusicPlayer();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	void OnLoadParam(const json& _json);

private:
	std::string smfPath_;  // smf‚ÌƒpƒX
};
