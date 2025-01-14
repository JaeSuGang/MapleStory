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
	CurrentIndex = 1;
	AccumulatedTime = 0.0f;
	TimePerFrame = 500;
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

/* 0.png ~ n.png ���·� �̸��� ���ĵǾ� �־�߸� ��� ������ */
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
	if (CurrentAnimation == Name)
		return;

	CurrentAnimation = Name;
	AccumulatedTime = 0.0f;
	CurrentIndex = 1;

	auto FindIter = Animations.find(Name);
	if (FindIter == Animations.end())
	{
		GEngine->DebugLog("��ȿ���� ���� �ִϸ��̼� Enum", 1);
		return;
	}
	else
	{
		vector<int>& TextureIDSequence = FindIter->second;

		MaterialToApply->TextureID = TextureIDSequence[CurrentIndex];

		RenderComponent->SetActorScaleByTextureSize();
	}
	TimePerFrame = FindIter->second[0];

}

void UAnimation::Play(float fDeltaTime)
{
	if (!MaterialToApply)
	{
		return;
	}

	AccumulatedTime += fDeltaTime;

	if (AccumulatedTime > TimePerFrame * 0.001f)
	{
		auto FindIter = Animations.find(CurrentAnimation);

		if (FindIter == Animations.end())
			GEngine->DebugLog("��ϵ��� ���� EAnimationName�� ���", 1);

		else
		{
			vector<int>& TextureIDSequence = FindIter->second;

			CurrentIndex < TextureIDSequence.size() - 1 ? CurrentIndex++ : CurrentIndex = 1;

			MaterialToApply->TextureID = TextureIDSequence[CurrentIndex];

			RenderComponent->SetActorScaleByTextureSize();

			AccumulatedTime = 0.0f;
		}
	}
}
