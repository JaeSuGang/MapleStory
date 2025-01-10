#include "GamePch.h"
#include "Actors/MobBase.h"
#include "RenderCore/RenderComponent.h"
#include "PhysicsCore/PhysicsComponent.h"

AMobBase::AMobBase()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();

	PhysicsComponent = CreateDefaultSubobject<UPhysicsComponent>();
}

void AMobBase::BeginPlay()
{
	Super::BeginPlay();

	RenderComponent->SetMeshIDByName("Plane");

	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);
	RenderComponent->SetBlendMode(0);
	RenderComponent->SetSortingLayer(20);
}

void AMobBase::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);
}
