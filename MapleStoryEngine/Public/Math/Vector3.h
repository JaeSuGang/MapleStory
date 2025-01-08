#pragma once
#include "EnginePch.h"

struct FVector3
{
public:
	ENGINE_API FVector3& operator+=(const FVector3& _Other);

public:
	float x;
	float y;
	float z;
};

