#include "GamePch.h"
#include "Actors/Skills/BP_GustShiftSkill_0.h"
#include "RenderCore/RenderComponent.h"

BP_GustShiftSkill_0::BP_GustShiftSkill_0()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}

void BP_GustShiftSkill_0::BeginPlay()
{
	Super::BeginPlay();

}

void BP_GustShiftSkill_0::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	if (Instigator)
	{
		FTransform& InstigatorTransform = Instigator->GetTransform();

		bool bIsLeftDirection = ((int)InstigatorTransform.Rotation.y % 360 < 90 || (int)InstigatorTransform.Rotation.y % 360 > 270);
		bool bIsUpDirection = (int)Transform.Rotation.z % 360 == 270;

		Transform.Position = InstigatorTransform.Position;

		if (bIsUpDirection)
			Transform.Position.y -= 90.0f;
		else
		{
			Transform.Rotation = InstigatorTransform.Rotation;
			Transform.Position.y -= 10.0f;
			if (bIsLeftDirection)
				Transform.Position.x += 90.0f;

			else
				Transform.Position.x -= 90.0f;
		}
	}
}

void BP_GustShiftSkill_0::InitAttributes()
{
	Super::InitAttributes();
}

void BP_GustShiftSkill_0::InitTexture()
{
	Super::InitTexture();

	RenderComponent->SetTextureByName("Resources\\Textures\\Skills\\13001024.effect.frames\\1.png");

	RenderComponent->SetActorScaleByTextureSize();
}

void BP_GustShiftSkill_0::InitAnimations()
{
	Super::InitAnimations();

	RenderComponent->AddAnimationByFolder(EAnimationName::Idle, "Resources\\Textures\\Skills\\13001024.effect.frames", 60);
}
