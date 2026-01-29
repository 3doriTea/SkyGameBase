#include "BaseCue.h"


BaseCue::BaseCue(
	const Vector2Int _position,
	const Vector2Int _canvasSize,
	const fs::path& _imageFile,
	const float _animTimeTotal) :
	GameObject{ "Simple.json" }
{
}

void BaseCue::Update()
{
}
