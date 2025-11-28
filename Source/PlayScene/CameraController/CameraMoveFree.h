#pragma once
#include "ICameraMove.h"

/// <summary>
/// ƒJƒƒ‰ˆÚ“®•û–@ - ©—R
/// </summary>
class CameraMoveFree : public ICameraMove
{
public:
	CameraMoveFree();
	~CameraMoveFree();

	void Start() override;
	void Update(ViewerCached& _system) override;
	void End() override;
};
