#include "GamePch.h"
#include "Actions/BP_JumpAction.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "Actor/Actor.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "RenderCore/RenderComponent.h"
#include "RenderCore/RenderSubsystem.h"

BP_JumpAction::BP_JumpAction()
{
	Tag = GameplayTagsManager->FindRegisteredTagExact("Action.Jump");
}

void BP_JumpAction::StartAction(AActor* Instigator)
{
	UPhysicsComponent* PhysicsComponent = Instigator->GetComponentByClass<UPhysicsComponent>();
	if (PhysicsComponent)
		PhysicsComponent->AddYVelocity(12.0f);

	URenderComponent* RenderComponent = Instigator->GetComponentByClass<URenderComponent>();
	if (RenderComponent)
	{
		RenderComponent->SetCurrentAnimation(EAnimationName::Jump);
	}
}
