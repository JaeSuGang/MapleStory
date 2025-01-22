#include "GamePch.h"
#include "Actors/Boss/BP_LucidFlower.h"
#include "RenderCore/RenderComponent.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "Attributes/AttributeComponent.h"
#include "Actions/ActionComponent.h"
#include "Actions/BP_TakeDamageAction.h"

BP_LucidFlower::BP_LucidFlower()
{
	ResourceName = "3005728.img";

	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}

void BP_LucidFlower::BeginPlay()
{
	Super::BeginPlay();

	this->InitTexture();

	this->InitAnimations();

	RenderComponent->SetCurrentAnimation(EAnimationName::Stand);
}

void BP_LucidFlower::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	RenderComponent->PlayAnimation(fDeltaTime);

	if (RenderComponent->GetHasPassedLastFrame())
	{
		if (RenderComponent->GetCurrentAnimation() == EAnimationName::Die)
			this->Destroy();
		else
			RenderComponent->SetCurrentAnimation(EAnimationName::Stand);
	}
}

void BP_LucidFlower::InitTexture()
{
	RenderComponent->SetMeshIDByName("Plane");

	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);

	RenderComponent->SetBlendMode(0);

	RenderComponent->SetSortingLayer(8);

	RenderComponent->SetTextureByName("Resources\\Textures\\Monsters\\" + ResourceName + "\\stand\\1.png");

	RenderComponent->SetActorScaleByTextureSize();
}

void BP_LucidFlower::InitAnimations()
{
	RenderComponent->EnableAnimation();

	RenderComponent->AddAnimationByFolder(EAnimationName::Stand, "Resources\\Textures\\Monsters\\" + ResourceName + "\\stand", 150);

	RenderComponent->AddAnimationByFolder(EAnimationName::Die, "Resources\\Textures\\Monsters\\" + ResourceName + "\\die", 150);

}

void BP_LucidFlower::SetResourcePath(string strPath)
{
	ResourceName = strPath;
}

