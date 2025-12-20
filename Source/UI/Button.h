#pragma once
#include <wtgb.h>

class Button : public GameObject
{
public:
	Button();
	~Button();



private:
	Vector2Int size_;
	Vector2Int position_;
	TextureHandle hOnImage_;
	TextureHandle hOffImage_;
};

