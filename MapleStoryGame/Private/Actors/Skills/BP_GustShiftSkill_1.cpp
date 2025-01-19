#include "GamePch.h"
#include "Actors/Skills/BP_GustShiftSkill_1.h"
#include "RenderCore/RenderComponent.h"

BP_GustShiftSkill_1::BP_GustShiftSkill_1()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}

void BP_GustShiftSkill_1::BeginPlay()
{
	Super::BeginPlay();



}

void BP_GustShiftSkill_1::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	if (Instigator)
	{
		FTransform& InstigatorTransform = Instigator->GetTransform();

		bool bIsLeftDirection = ((int)InstigatorTransform.Rotation.y % 360 < 90 || (int)InstigatorTransform.Rotation.y % 360 > 270);
		bool bIsUpDirection = (int)Transform.Rotation.z % 360 == 270;

		Transform.Position = InstigatorTransform.Position;

		if (bIsUpDirection)
			Transform.Position.y -= 150.0f;
		else
		{
			Transform.Rotation = InstigatorTransform.Rotation;
			if (bIsLeftDirection)
				Transform.Position.x += 150.0f;
			else
				Transform.Position.x -= 150.0f;
		}
	}
}

void BP_GustShiftSkill_1::InitAttributes()
{
	Super::InitAttributes();
}

void BP_GustShiftSkill_1::InitTexture()
{
	Super::InitTexture();

	RenderComponent->SetTextureByName("Resources\\Textures\\Skills\\13001024.effect0.frames\\1.png");

	RenderComponent->SetActorScaleByTextureSize();
}

void BP_GustShiftSkill_1::InitAnimations()
{
	Super::InitAnimations();

	RenderComponent->AddAnimationByFolder(EAnimationName::Idle, "Resources\\Textures\\Skills\\13001024.effect0.frames", 60);
}
