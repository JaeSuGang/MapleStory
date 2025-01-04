#pragma once
#include "EnginePch.h"
#include "UObject/Object.h"

class UMaterial;

enum class EAnimationName
{
	Screen
};

class UAnimation : public UObject
{
public:
	/* 생성자와 오버라이드 */
	ENGINE_API UAnimation();

public:
	ENGINE_API void SetTimePerFrame(float fTime);

	ENGINE_API void SetMaterialToApply(UMaterial* Material);

	ENGINE_API void AddAnimationByFolder(EAnimationName Name, string strFolderDir);

	ENGINE_API void AddAnimation(EAnimationName Name, vector<int>TextureIDSequence);

	ENGINE_API void SetCurrentAnimation(EAnimationName Name);

	ENGINE_API void Play(float fDeltaTime);

protected:
	UMaterial* MaterialToApply;
	unordered_map<EAnimationName, vector<int>> Animations;
	EAnimationName CurrentAnimation;
	int CurrentIndex;
	float AccumulatedTime;
	float TimePerFrame;
};

