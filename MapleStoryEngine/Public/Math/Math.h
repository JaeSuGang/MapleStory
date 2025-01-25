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

inline float NormalizeDirectionAngle(float _Angle)
{
	_Angle = std::fmodf(_Angle, 360.0f);

	if (_Angle > 180.0f)
		return _Angle - 360.0f;

	else if (_Angle < -180.0f)
		return _Angle + 360.0f;

	else
		return _Angle;
}

inline float GetZAngle(FVector3 _Pos, FVector3 _TargetPos, FVector3 _Rot)
{
	_TargetPos.x -= _Pos.x;
	_TargetPos.y -= _Pos.y;

	float _PositionalDegree = RadianToDegree(std::atan2f(_TargetPos.y, _TargetPos.x));
	float _LookDegree = _Rot.z;

	float _ReturnVal = _PositionalDegree - _LookDegree;

	return NormalizeDirectionAngle(_ReturnVal);
}