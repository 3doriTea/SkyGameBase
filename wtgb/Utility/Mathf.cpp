#include "pch\pch.h"
#include "Mathf.h"

wtgb::Mathf::Randomer::Randomer(const uint32_t _seed) :
	randomEngine_{ _seed }
{
}

wtgb::Mathf::Randomer::Randomer() :
	Randomer{ std::random_device{}() }
{
}

wtgb::Mathf::Randomer::~Randomer()
{
}

int wtgb::Mathf::Randomer::NextInt(int _max)
{
	std::uniform_int_distribution<int> dist{ 0, _max };
	return dist(randomEngine_);
}

float wtgb::Mathf::Randomer::Rand()
{
	std::uniform_real_distribution<float> dist{ 0.0f, 1.0f };
	return dist(randomEngine_);
}

float wtgb::Mathf::InvLerp(const float _min, const float _max, const float _value)
{
	if (_value <= _min)
	{
		return 0.0f;
	}
	else if (_value >= _max)
	{
		return 1.0f;
	}
	else
	{
		return (_value - _min) / (_max - _min);
	}
}

wtgb::Vector3 wtgb::Mathf::Lerp(const Vector3 _a, const Vector3 _b, const float _rate)
{
	return _a + DirectX::XMVectorScale((_b - _a), _rate);
}

wtgb::Vector2 wtgb::Mathf::Lerp(const Vector2 _a, const Vector2 _b, const float _rate)
{
	return _a + DirectX::XMVectorScale((_b - _a), _rate);
}

float wtgb::Mathf::Lerp(const float _a, const float _b, const float _rate)
{
	return _a + ((_b - _a) * _rate);
}
