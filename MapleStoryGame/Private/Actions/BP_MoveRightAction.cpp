#include "GamePch.h"
#include "Actions/BP_MoveRightAction.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "Actor/Actor.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "RenderCore/RenderComponent.h"
#include "Attributes/AttributeComponent.h"

BP_MoveRightAction::BP_MoveRightAction()
{
	Tag = GameplayTagsManager->FindRegisteredTagExact("Action.MoveRight");
}

void BP_MoveRightAction::StartAction(AActor* Instigator)
{
	float fDeltaTime = GEngine->TimeSubsystem->GetDeltaTime();

	FTransform _Transform = Instigator->GetTransform();
	_Transform.Rotation.y = 180;
	Instigator->SetRotation(_Transform.Rotation);

	/* TagComponent */
	UAttributeComponent* AttributeComponent = Instigator->GetComponentByClass<UAttributeComponent>();
	if (AttributeComponent)
	{
		AttributeComponent->AddAttribute("Status.Walking");
	}

	/* PhysicsComponent */
	UPhysicsComponent* PhysicsComponent = Instigator->GetComponentByClass<UPhysicsComponent>();
	if (PhysicsComponent)
	{
		FVector3 Velocity = PhysicsComponent->GetVelocity();

		if (!AttributeComponent->HasAttributeExact("Status.Falling"))
		{
			if (Velocity.x <= 4.0f)
				PhysicsComponent->SetXVelocity(4.0f);
		}

		else
		{
			if (Velocity.x <= 4.0f)
				PhysicsComponent->AddXVelocity(10.0f * fDeltaTime);
		}
	}

	/* RenderComponent */
	URenderComponent* RenderComponent = Instigator->GetComponentByClass<URenderComponent>();
	if (RenderComponent)
	{
		RenderComponent->SetCurrentAnimation(EAnimationName::Walk);
	}
}
