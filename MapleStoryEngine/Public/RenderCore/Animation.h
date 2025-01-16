#pragma once
#include "EnginePch.h"
#include "UObject/Object.h"
#include "Actor/Actor.h"

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

struct FAnimationEvent
{
	EAnimationName AnimationName;
	int AnimationIndex;
	std::function<void()> Function;
};

class UAnimation : public UObject
{
	friend class URenderComponent;

public:
	/* 생성자와 오버라이드 */
	ENGINE_API UAnimation();

public:
	ENGINE_API void AddAnimationEvent(EAnimationName _AnimationName, int _Sequence, std::function<void()> _Function);

	ENGINE_API void AddAnimationEvent(FAnimationEvent _AnimationEvent);

	ENGINE_API void SetRenderComponent(URenderComponent* _Component);

	ENGINE_API void SetTimePerFrame(int nTime);

	ENGINE_API void SetMaterialToApply(UMaterial* Material);

	ENGINE_API void AddAnimationByFolder(EAnimationName Name, string strFolderDir, int nTimePerFrame);

	ENGINE_API void AddAnimation(EAnimationName Name, vector<int>TextureIDSequence);

	ENGINE_API void SetCurrentAnimation(EAnimationName Name);

	ENGINE_API void Play(float fDeltaTime);

protected:
	void CheckAnimationEvents();

protected:
	URenderComponent* RenderComponent;
	UMaterial* MaterialToApply;
	unordered_map<EAnimationName, vector<int>> Animations;
	vector<FAnimationEvent> AnimationEvents;
	EAnimationName CurrentAnimation;
	int CurrentIndex;
	float AccumulatedTime;
	int TimePerFrame;
	bool HasPassedLastFrame;
};

