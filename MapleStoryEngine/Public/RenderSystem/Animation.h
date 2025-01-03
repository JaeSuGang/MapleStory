#pragma once
#include "EnginePch.h"
#include "UObject/Object.h"

class UMaterial;

class UAnimation : public UObject
{
public:
	ENGINE_API void SetMaterialToApply(UMaterial* Material);

	ENGINE_API void Play(float fDeltaTime);

protected:
	UMaterial* MaterialToApply;
	vector<int> TextureIDInSequence;
	int CurrentIndex;
	float AccumulatedTime;
	float TimePerFrame;
};

