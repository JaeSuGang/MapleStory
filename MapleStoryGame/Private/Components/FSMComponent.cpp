#include "GamePch.h"
#include "Components/FSMComponent.h"

void UFSMComponent::BeginPlay()
{

}

void UFSMComponent::TickComponent(float fDeltaTime)
{

}

void UBaseState::SetOwner(AActor* OwnerToSet)
{
	Owner = OwnerToSet;
}

void UBaseState::SetFSM(UFSMComponent* FSMToSet)
{
	FSM = FSMToSet;
}
