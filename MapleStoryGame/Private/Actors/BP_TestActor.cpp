#include "GamePch.h"
#include "Actors/BP_TestActor.h"
#include "RenderCore/RenderComponent.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "Actions/ActionComponent.h"


BP_TestActor::BP_TestActor()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();

	PhysicsComponent = CreateDefaultSubobject<UPhysicsComponent>();
}

void BP_TestActor::BeginPlay()
{
	Super::BeginPlay();
	string strMeshName = "Plane";
	string strTextureName = "Resources\\Textures\\9000404.img.stand.0.png";
	RenderComponent->SetMeshIDByName(strMeshName);
	RenderComponent->SetTextureByName(strTextureName);
	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);
	RenderComponent->SetBlendMode(0);
	RenderComponent->SetActorScaleByTextureSize();

	PhysicsComponent->InitializeAsDynamicRigidBody(Transform.Scale.x, Transform.Scale.y);
}

void BP_TestActor::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);
}
