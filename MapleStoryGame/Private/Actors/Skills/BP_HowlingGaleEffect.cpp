#include "GamePch.h"
#include "RenderCore/RenderComponent.h"
#include "World/World.h"

#include "Actors/Skills/BP_HowlingGaleEffect.h"
#include "Actors/Skills/BP_HowlingGaleBall.h"

BP_HowlingGaleEffect::BP_HowlingGaleEffect()
{
	HasSpawnedBall = false;

	SpawnBallTimer = 0.6f;

	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}

void BP_HowlingGaleEffect::BeginPlay()
{
	Super::BeginPlay();

}

void BP_HowlingGaleEffect::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	SpawnBallTimer -= fDeltaTime;

	if (Instigator)
	{
		FTransform& InstigatorTransform = Instigator->GetTransform();

		bool bIsLeftDirection = ((int)InstigatorTransform.Rotation.y % 360 < 90 || (int)InstigatorTransform.Rotation.y % 360 > 270);

		Transform.Position = InstigatorTransform.Position;

		Transform.Rotation = InstigatorTransform.Rotation;
		if (bIsLeftDirection)
			Transform.Position.x -= 90.0f;

		else
			Transform.Position.x += 90.0f;
	}

	if (!HasSpawnedBall && SpawnBallTimer <= 0.0f)
	{
		HasSpawnedBall = true;

		FTransform& InstigatorTransform = Instigator->GetTransform();
		bool bIsLeftDirection = ((int)InstigatorTransform.Rotation.y % 360 < 90 || (int)InstigatorTransform.Rotation.y % 360 > 270);

		BP_HowlingGaleBall* HowlingGaleBall = GetWorld()->SpawnActor<BP_HowlingGaleBall>();
		HowlingGaleBall->SetInstigator(Instigator);
		FVector3 _BallPos = Instigator->GetTransform().Position;
		if (bIsLeftDirection)
			_BallPos.x -= 100.0f;
		else
			_BallPos.x += 100.0f;
		_BallPos.y += 400.0f;
		HowlingGaleBall->SetPosition(_BallPos);
	}
}

void BP_HowlingGaleEffect::InitAttributes()
{
	Super::InitAttributes();
}

void BP_HowlingGaleEffect::InitTexture()
{
	Super::InitTexture();

	RenderComponent->SetTextureByName("Resources\\Textures\\Skills\\HowlingGale\\effect\\1.png");

	RenderComponent->SetActorScaleByTextureSize();
}

void BP_HowlingGaleEffect::InitAnimations()
{
	Super::InitAnimations();

	RenderComponent->AddAnimationByFolder(EAnimationName::Idle, "Resources\\Textures\\Skills\\HowlingGale\\effect", 60);
}
