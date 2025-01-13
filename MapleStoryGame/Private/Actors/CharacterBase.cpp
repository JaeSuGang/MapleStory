#include "GamePch.h"
#include "Actors/CharacterBase.h"
#include "RenderCore/RenderComponent.h"
#include "PhysicsCore/PhysicsComponent.h"


ACharacterBase::ACharacterBase()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();

	PhysicsComponent = CreateDefaultSubobject<UPhysicsComponent>();

}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	RenderComponent->SetMeshIDByName("Plane");

	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);

	RenderComponent->SetBlendMode(0);

	RenderComponent->SetSortingLayer(9);

	RenderComponent->SetTextureByName("Resources\\Textures\\Avatar\\stand_0.png");

	RenderComponent->SetActorScaleByTextureSize();

	PhysicsComponent->InitializeAsMobFoot(1.0f, Transform.Scale.y * -0.49f, MOB_COLLISION_FLAG);
}

void ACharacterBase::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);
}