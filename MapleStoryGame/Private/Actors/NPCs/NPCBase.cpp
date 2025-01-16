#include "GamePch.h"
#include "Actors/NPCs/NPCBase.h"

ANPCBase::ANPCBase()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}

void ANPCBase::BeginPlay()
{
	Super::BeginPlay();

	RenderComponent->SetMeshIDByName("Plane");

	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);
	RenderComponent->SetBlendMode(0);
	RenderComponent->SetSortingLayer(8);
}

void ANPCBase::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);
}