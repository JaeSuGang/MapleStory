#include "EnginePch.h"
#include "Engine/Engine.h"
#include "RenderCore/RenderSubsystem.h"
#include "RenderCore/Animation.h"
#include "RenderCore/Material.h"
#include "RenderCore/RenderComponent.h"

UAnimation::UAnimation()
	:
	CurrentAnimation{},
	MaterialToApply{}
{
	HasPassedLastFrame = false;
	CurrentIndex = 1;
	AccumulatedTime = 0.0f;
	TimePerFrame = 500;
}

/* 반드시 함수의 주체 Instigator는 이 애니메이션을 소유한 Actor일 것 */
void UAnimation::AddAnimationEvent(EAnimationName _AnimationName, int _Sequence, std::function<void()> _Function)
{
	this->AddAnimationEvent(FAnimationEvent{ _AnimationName, _Sequence, _Function });
}

/* 반드시 함수의 주체 Instigator는 이 애니메이션을 소유한 Actor일 것 */
void UAnimation::AddAnimationEvent(FAnimationEvent _AnimationEvent)
{
	AnimationEvents.push_back(_AnimationEvent);
}

void UAnimation::SetRenderComponent(URenderComponent* _Component)
{
	RenderComponent = _Component;
}

void UAnimation::SetTimePerFrame(int nTime)
{
	TimePerFrame = nTime;
}

void UAnimation::SetMaterialToApply(UMaterial* Material)
{
	MaterialToApply = Material;
}

/* 1.png ~ n.png 형태로 이름이 정렬되어 있어야만 사용 가능함 */
void UAnimation::AddAnimationByFolder(EAnimationName Name, string strFolderDir, int nTimePerFrame)
{
	auto FindIter = Animations.find(Name);

	if (FindIter != Animations.end())
		return;

	this->AddAnimation(Name, vector<int>{});
	FindIter = Animations.find(Name);

	vector<int>& IDConsequence = FindIter->second;

	IDConsequence.push_back(nTimePerFrame);
	int nIndex = 1;
	int nMissingTexture = GEngine->RenderSubsystem->MissingTextureTextureID;
	while (true)
	{
		string TextureName = strFolderDir + "\\" + std::to_string(nIndex) + ".png";
		int TextureID = GEngine->RenderSubsystem->GetTextureIDByName(TextureName);

		if (TextureID == nMissingTexture)
			break;

		IDConsequence.push_back(TextureID);

		nIndex++;
	}
}

void UAnimation::AddAnimation(EAnimationName Name, vector<int> TextureIDSequence)
{
	Animations.insert(std::make_pair(Name, TextureIDSequence));
}

void UAnimation::SetCurrentAnimation(EAnimationName Name)
{
	auto FindIter = Animations.find(Name);
	if (FindIter == Animations.end())
	{
		return;
	}
	else
	{
		if (CurrentAnimation != Name)
		{
			CurrentAnimation = Name;
			AccumulatedTime = 0.0f;
			CurrentIndex = 1;
			HasPassedLastFrame = false;
		}

		vector<int>& TextureIDSequence = FindIter->second;

		MaterialToApply->TextureID = TextureIDSequence[CurrentIndex];

		RenderComponent->SetActorScaleByTextureSize();
	}

	TimePerFrame = FindIter->second[0];
}

void UAnimation::Play(float fDeltaTime)
{
	if (!MaterialToApply)
		return;

	AccumulatedTime += fDeltaTime;

	if (AccumulatedTime < TimePerFrame * 0.001f)
		return;

	auto FindIter = Animations.find(CurrentAnimation);

	if (FindIter == Animations.end())
		GEngine->DebugLog("등록되지 않은 EAnimationName을 사용", 1);

	else
	{
		vector<int>& TextureIDSequence = FindIter->second;

		if (CurrentIndex < TextureIDSequence.size() - 1)
			CurrentIndex++;

		else
			CurrentIndex = 1;

		if (CurrentIndex == TextureIDSequence.size() - 2)
			HasPassedLastFrame = true;


		MaterialToApply->TextureID = TextureIDSequence[CurrentIndex];

		RenderComponent->SetActorScaleByTextureSize();

		AccumulatedTime = 0.0f;

		this->CheckAnimationEvents();
	}
}

void UAnimation::CheckAnimationEvents()
{
	auto LoopIter = AnimationEvents.begin();

	while (LoopIter != AnimationEvents.end())
	{
		FAnimationEvent& AnimationEvent = *LoopIter;

		if (CurrentAnimation != AnimationEvent.AnimationName || CurrentIndex != AnimationEvent.AnimationIndex)
		{
			++LoopIter;
			continue;
		}

		AnimationEvent.Function();
		LoopIter = AnimationEvents.erase(LoopIter);
	}
}