#include "GamePch.h"
#include "Actions/BP_MoveLeftAction.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "Actor/Actor.h"
#include "PhysicsCore/PhysicsComponent.h"

BP_MoveLeftAction::BP_MoveLeftAction()
{
	Tag = GameplayTagsManager->FindRegisteredTagExact("Action.MoveLeft");
}

void BP_MoveLeftAction::StartAction(AActor* Instigator)
{
	UPhysicsComponent* PhysicsComponent = Instigator->GetComponentByClass<UPhysicsComponent>();

	if (!PhysicsComponent)
		return;

	PhysicsComponent->SetXVelocity(-500.0f);
}
