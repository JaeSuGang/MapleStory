#include "GamePch.h"
#include "RenderCore/RenderComponent.h"
#include "World/World.h"

#include "Actors/Skills/BP_SongOfHeavenEffect.h"



BP_SongOfHeavenEffect::BP_SongOfHeavenEffect()
{
	LifeTime = 0.0f;

	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}

void BP_SongOfHeavenEffect::BeginPlay()
{
	Super::BeginPlay();

	RenderComponent->SetCurrentAnimation(EAnimationName::Revive);
}

void BP_SongOfHeavenEffect::Tick(float fDeltaTime)
{
	ElapsedTime += fDeltaTime;

	SetPositionRelativeToInstigator(100.0f, 0.0f);
	SetRotation(Instigator->GetTransform().Rotation);

	if (RenderComponent->GetCurrentAnimation() == EAnimationName::Revive && RenderComponent->GetHasPassedLastFrame())
		RenderComponent->SetCurrentAnimation(EAnimationName::Idle);

	if (LifeTime <= 0.0f)
		RenderComponent->SetCurrentAnimation(EAnimationName::Die);

	if (RenderComponent->GetCurrentAnimation() == EAnimationName::Die && RenderComponent->GetHasPassedLastFrame())
		this->Destroy();

	RenderComponent->PlayAnimation(fDeltaTime);

	LifeTime -= fDeltaTime;
}

void BP_SongOfHeavenEffect::InitAttributes()
{
	Super::InitAttributes();
}

void BP_SongOfHeavenEffect::InitTexture()
{
	Super::InitTexture();

	RenderComponent->SetTextureByName("Resources\\Textures\\Skills\\SongOfHeaven\\effect\\1.png");

	RenderComponent->SetActorScaleByTextureSize();

}

void BP_SongOfHeavenEffect::InitAnimations()
{
	Super::InitAnimations();

	RenderComponent->AddAnimationByFolder(EAnimationName::Revive, "Resources\\Textures\\Skills\\SongOfHeaven\\effect", 30);

	RenderComponent->AddAnimationByFolder(EAnimationName::Idle, "Resources\\Textures\\Skills\\SongOfHeaven\\loopEffect", 60);

	RenderComponent->AddAnimationByFolder(EAnimationName::Die, "Resources\\Textures\\Skills\\SongOfHeaven\\die", 60);

	
}

void BP_SongOfHeavenEffect::AddLifeTime(float fDeltaTime)
{
	LifeTime += fDeltaTime;

	LifeTime = LifeTime > 0.1f ? 0.1f : LifeTime;
}
