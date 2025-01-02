#include "GamePch.h"
#include "Actors/BP_TestActor.h"
#include "ActorComponent/RenderComponent.h"
#include "Actions/ActionComponent.h"

BP_TestActor::BP_TestActor()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}
