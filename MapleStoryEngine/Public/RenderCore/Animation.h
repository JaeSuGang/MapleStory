#pragma once
#include "EnginePch.h"
#include "UObject/Object.h"

class UMaterial;
class URenderComponent;

enum class EAnimationName
{
	Idle,
	Walk,
	Jump,
	SwingT1,
	Screen
};

class UAnimation : public UObject
{
public:
	/* 생성자와 오버라이드 */
	ENGINE_API UAnimation();

public:
	ENGINE_API void SetRenderComponent(URenderComponent* _Component);

	ENGINE_API void SetTimePerFrame(int nTime);

	ENGINE_API void SetMaterialToApply(UMaterial* Material);

	ENGINE_API void AddAnimationByFolder(EAnimationName Name, string strFolderDir, int nTimePerFrame);

	ENGINE_API void AddAnimation(EAnimationName Name, vector<int>TextureIDSequence);

	ENGINE_API void SetCurrentAnimation(EAnimationName Name);

	ENGINE_API void Play(float fDeltaTime);

protected:
	URenderComponent* RenderComponent;
	UMaterial* MaterialToApply;
	unordered_map<EAnimationName, vector<int>> Animations;
	EAnimationName CurrentAnimation;
	int CurrentIndex;
	float AccumulatedTime;
	int TimePerFrame;
};

