#include "GamePch.h"
#include "Actors/BP_TestActor.h"
#include "RenderSystem/RenderComponent.h"
#include "Actions/ActionComponent.h"

BP_TestActor::BP_TestActor()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}

void BP_TestActor::BeginPlay()
{

}

void BP_TestActor::Tick(float fDeltaTime)
{

}
