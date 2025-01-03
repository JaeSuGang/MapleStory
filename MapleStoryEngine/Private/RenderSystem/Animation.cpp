#include "EnginePch.h"
#include "RenderSystem/Animation.h"
#include "RenderSystem/Material.h"

ENGINE_API void UAnimation::SetMaterialToApply(UMaterial* Material)
{
	MaterialToApply = Material;
}

ENGINE_API void UAnimation::Play(float fDeltaTime)
{
	if (MaterialToApply)

	AccumulatedTime += fDeltaTime;

	if (AccumulatedTime > TimePerFrame)
	{
		AccumulatedTime = 0.0f;
		CurrentIndex++;
		MaterialToApply->TextureID = TextureIDInSequence[CurrentIndex];
	}
}
