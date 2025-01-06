#include "EnginePch.h"
#include "Engine/Engine.h"
#include "RenderCore/RenderSubsystem.h"
#include "RenderCore/Animation.h"
#include "RenderCore/Material.h"

UAnimation::UAnimation()
	:
	CurrentAnimation{},
	MaterialToApply{}
{
	CurrentIndex = 0;
	AccumulatedTime = 0.0f;
	TimePerFrame = 0.06f;
}

void UAnimation::SetTimePerFrame(float fTime)
{

}

void UAnimation::SetMaterialToApply(UMaterial* Material)
{
	MaterialToApply = Material;
}

/* 0.png ~ n.png 형태로 이름이 정렬되어 있어야만 사용 가능함 */
void UAnimation::AddAnimationByFolder(EAnimationName Name, string strFolderDir)
{
	auto FindIter = Animations.find(Name);

	if (FindIter == Animations.end())
	{
		this->AddAnimation(Name, vector<int>{});
		FindIter = Animations.find(Name);
	}

	int nIndex = 0;
	int nMissingTexture = GEngine->RenderSubsystem->MissingTextureTextureID;
	while (true)
	{
		string TextureName = strFolderDir + "\\" + std::to_string(nIndex) + ".png";
		int TextureID = GEngine->RenderSubsystem->GetTextureIDByName(TextureName);

		if (TextureID == nMissingTexture)
			break;

		FindIter->second.push_back(TextureID);

		nIndex++;
	}

}

void UAnimation::AddAnimation(EAnimationName Name, vector<int> TextureIDSequence)
{
	Animations.insert(std::make_pair(Name, TextureIDSequence));
}

void UAnimation::SetCurrentAnimation(EAnimationName Name)
{
	CurrentAnimation = Name;
	AccumulatedTime = 0.0f;
	CurrentIndex = 0;
}

void UAnimation::Play(float fDeltaTime)
{
	if (!MaterialToApply)
		return;

	AccumulatedTime += fDeltaTime;

	if (AccumulatedTime > TimePerFrame)
	{
		auto FindIter = Animations.find(CurrentAnimation);

		if (FindIter == Animations.end())
			GEngine->DebugLog("등록되지 않은 EAnimationName을 사용", 1);

		else
		{
			vector<int>& TextureIDSequence = FindIter->second;

			CurrentIndex < TextureIDSequence.size() - 1 ? CurrentIndex++ : CurrentIndex = 0;

			MaterialToApply->TextureID = (FindIter->second)[CurrentIndex];

			AccumulatedTime = 0.0f;
		}
	}
}
