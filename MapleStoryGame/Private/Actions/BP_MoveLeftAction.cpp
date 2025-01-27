#include "GamePch.h"
#include "Actions/BP_MoveLeftAction.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "Actor/Actor.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "RenderCore/RenderComponent.h"
#include "RenderCore/RenderSubsystem.h"
#include "Attributes/AttributeComponent.h"

BP_MoveLeftAction::BP_MoveLeftAction()
{
	Tag = GameplayTagsManager->FindRegisteredTagExact("Action.MoveLeft");
}

void BP_MoveLeftAction::StartAction(AActor* Instigator)
{
	float fDeltaTime = GEngine->TimeSubsystem->GetDeltaTime();

	/* TagComponent */
	UAttributeComponent* AttributeComponent = Instigator->GetComponentByClass<UAttributeComponent>();
	if (AttributeComponent)
	{
		if (AttributeComponent->ContainsAttribute("Status.Attacking.Shoot1"))
			return;

		if (AttributeComponent->ContainsAttribute("Status.Attacking.SwingT1"))
			return;

		if (AttributeComponent->HasAttributeExact("Status.Proning"))
			return;

		AttributeComponent->AddAttribute("Status.Walking");
	}

	FTransform _Transform = Instigator->GetTransform();
	_Transform.Rotation.y = 0;
	Instigator->SetRotation(_Transform.Rotation);

	/* PhysicsComponent */
	UPhysicsComponent* PhysicsComponent = Instigator->GetComponentByClass<UPhysicsComponent>();
	if (PhysicsComponent)
	{
		FVector3 Velocity = PhysicsComponent->GetVelocity();

		if (!AttributeComponent->HasAttributeExact("Status.Falling"))
		{
			if (Velocity.x >= -200.0f)
				PhysicsComponent->SetXVelocity(-200.0f);
		}

		else
		{
			if (Velocity.x >= -200.0f)
				PhysicsComponent->AddXVelocity(-500.0f * fDeltaTime);
		}
	}

	/* RenderComponent */
	URenderComponent* RenderComponent = Instigator->GetComponentByClass<URenderComponent>();
	if (RenderComponent)
	{
		RenderComponent->SetCurrentAnimation(EAnimationName::Walk);
	}
}
