#include "GamePch.h"
#include "Actors/NPCs/NPCBase.h"

ANPCBase::ANPCBase()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();

	PhysicsComponent = CreateDefaultSubobject<UPhysicsComponent>();
}

void ANPCBase::BeginPlay()
{
	Super::BeginPlay();

	RenderComponent->SetMeshIDByName("Plane");

	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);

	RenderComponent->SetBlendMode(0);

	RenderComponent->SetSortingLayer(RENDER_LAYER_MONSTER);

}

void ANPCBase::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);
}

void ANPCBase::InitPhysics()
{
	PhysicsComponent->InitializeBody(b2BodyType::b2_dynamicBody);

	PhysicsComponent->InitializeNPCFootCollider();
}
