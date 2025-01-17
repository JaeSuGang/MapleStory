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

	/* TagComponent */
	UAttributeComponent* AttributeComponent = Instigator->GetComponentByClass<UAttributeComponent>();
	if (AttributeComponent)
	{
		if (AttributeComponent->ContainsAttribute("Status.Attacking"))
			return;

		if (AttributeComponent->HasAttributeExact("Status.Proning"))
			return;

		AttributeComponent->AddAttribute("Status.Walking");
	}

	FTransform _Transform = Instigator->GetTransform();
	_Transform.Rotation.y = 180;
	Instigator->SetRotation(_Transform.Rotation);


	/* PhysicsComponent */
	UPhysicsComponent* PhysicsComponent = Instigator->GetComponentByClass<UPhysicsComponent>();
	if (PhysicsComponent)
	{
		FVector3 Velocity = PhysicsComponent->GetVelocity();

		if (!AttributeComponent->HasAttributeExact("Status.Falling"))
		{
			if (Velocity.x <= 200.0f)
				PhysicsComponent->SetXVelocity(200.0f);
		}

		else
		{
			if (Velocity.x <= 200.0f)
				PhysicsComponent->AddXVelocity(500.0f * fDeltaTime);
		}
	}

	/* RenderComponent */
	URenderComponent* RenderComponent = Instigator->GetComponentByClass<URenderComponent>();
	if (RenderComponent)
	{
		RenderComponent->SetCurrentAnimation(EAnimationName::Walk);
	}
}
