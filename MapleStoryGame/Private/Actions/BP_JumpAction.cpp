#include "GamePch.h"
#include "Actions/BP_JumpAction.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "Actor/Actor.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "RenderCore/RenderComponent.h"
#include "RenderCore/RenderSubsystem.h"
#include "Attributes/AttributeComponent.h"
#include "Engine/Engine.h"
#include "Engine/KeyInputSubsystem.h"

BP_JumpAction::BP_JumpAction()
{
	Tag = GameplayTagsManager->FindRegisteredTagExact("Action.Jump");
}

void BP_JumpAction::StartAction(AActor* Instigator)
{
	UAttributeComponent* AttributeComponent = Instigator->GetComponentByClass<UAttributeComponent>();
	if (AttributeComponent && AttributeComponent->HasAttributeExact("Status.Falling"))
		return;

	bool bIsDownPressed = GEngine->KeyInputSubsystem->GetKey(VK_DOWN, UKeyInputSubsystem::EKeyState::Triggered);

	if (bIsDownPressed)
	{
		UPhysicsComponent* PhysicsComponent = Instigator->GetComponentByClass<UPhysicsComponent>();
		if (PhysicsComponent)
			PhysicsComponent->AddYPosition(-2.0f);

		URenderComponent* RenderComponent = Instigator->GetComponentByClass<URenderComponent>();
		if (RenderComponent)
		{
			RenderComponent->SetCurrentAnimation(EAnimationName::Jump);
		}
	}
	else
	{
		UPhysicsComponent* PhysicsComponent = Instigator->GetComponentByClass<UPhysicsComponent>();
		if (PhysicsComponent)
			PhysicsComponent->AddYVelocity(600.0f);

		URenderComponent* RenderComponent = Instigator->GetComponentByClass<URenderComponent>();
		if (RenderComponent)
		{
			RenderComponent->SetCurrentAnimation(EAnimationName::Jump);
		}
	}
}
