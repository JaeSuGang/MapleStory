#include "GamePch.h"
#include "Actors/BP_TestFloor.h"
#include "RenderCore/RenderComponent.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "Actions/ActionComponent.h"


BP_TestFloor::BP_TestFloor()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();

	PhysicsComponent = CreateDefaultSubobject<UPhysicsComponent>();
}

void BP_TestFloor::BeginPlay()
{
	Super::BeginPlay();

	Transform.Position.y = -400.0f;


	RenderComponent->SetMeshIDByName("Plane");
	RenderComponent->SetBlendMode(0);
	RenderComponent->SetTextureByName("Resources\\Textures\\foothold.0.0.png");
	RenderComponent->SetActorScaleByTextureSize();
	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);

	PhysicsComponent->InitializeAsStatic(Transform.Scale.x, Transform.Scale.y);
}

void BP_TestFloor::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);
}
