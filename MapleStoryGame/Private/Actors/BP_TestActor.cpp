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

	PhysicsComponent->InitializeAsDynamicRigidBody();
}

void BP_TestActor::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);
}
