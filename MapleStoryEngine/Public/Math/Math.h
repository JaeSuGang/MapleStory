#pragma once
#include "EnginePch.h"
#include "Math/Vector3.h"

inline float DegreeToRadian(float _Deg)
{
	return _Deg / 180.0f * std::acos(-1.0f);
}

inline float RadianToDegree(float _Rad)
{
	return _Rad * 180.0f / std::acos(-1.0f);
}

inline float GetZAngle(FVector3 _First, FVector3 _Second)
{
	float _FirstAngle = RadianToDegree(std::atan2(_First.y, _First.x));
	float _SecondAngle = RadianToDegree(std::atan2(_Second.y, _Second.x));

	float _AngleDiff = _SecondAngle - _FirstAngle;

	return _AngleDiff > 180.0f ? -(_AngleDiff - 180.0f) : _AngleDiff;
}