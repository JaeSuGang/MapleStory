#include "GamePch.h"
#include "Actions/BP_MoveRightAction.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "Actor/Actor.h"
#include "PhysicsCore/PhysicsComponent.h"

BP_MoveRightAction::BP_MoveRightAction()
{
	Tag = GameplayTagsManager->FindRegisteredTagExact("Action.MoveRight");
}

void BP_MoveRightAction::StartAction(AActor* Instigator)
{
	UPhysicsComponent* PhysicsComponent = Instigator->GetComponentByClass<UPhysicsComponent>();

	if (!PhysicsComponent)
		return;

	PhysicsComponent->SetXVelocity(500.0f);
}
