#include "EnginePch.h"
#include "ActorComponent/ActorComponent.h"

void UActorComponent::TickComponent(float fDeltaTime)
{

}

void UActorComponent::SetOwner(AActor* pOwner)
{
	Owner = pOwner;
}
