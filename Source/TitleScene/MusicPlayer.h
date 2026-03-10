#pragma once
#include <wtgb.h>

/// <summary>
/// 単純に曲を流す
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
	std::string smfPath_;           // smfのパス
	std::string toneAudioFilePath_;  // 再生する音の音源ファイルのパス
};
