#pragma once
#include "EnginePch.h"

inline float DegreeToRadian(float _Deg)
{
	return _Deg / 180.0f * std::acos(-1.0f);
}

inline float RadianToDegree(float _Rad)
{
	return _Rad * 180.0f / std::acos(-1.0f);
}