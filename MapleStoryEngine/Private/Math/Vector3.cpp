#include "EnginePch.h"
#include "Math/Vector3.h"


FVector3& FVector3::operator+=(const FVector3& _Other)
{
	this->x += _Other.x;
	this->y += _Other.y;
	this->z += _Other.z;

	return *this;
}