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

	void OnLoadParam(const json& _json);

private:
	EntityId titleNeco_;
	Vector3 position_;
	Vector3 targetBegin_;
	Vector3 targetEnd_;
};
