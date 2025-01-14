#include "GamePch.h"
#include "Actions/BP_MoveLeftAction.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "Actor/Actor.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "RenderCore/RenderComponent.h"
#include "RenderCore/RenderSubsystem.h"

BP_MoveLeftAction::BP_MoveLeftAction()
{
	Tag = GameplayTagsManager->FindRegisteredTagExact("Action.MoveLeft");
}

void BP_MoveLeftAction::StartAction(AActor* Instigator)
{
	float fDeltaTime = GEngine->TimeSubsystem->GetDeltaTime();

	FTransform _Transform = Instigator->GetTransform();
	_Transform.Rotation.y = 0;
	Instigator->SetRotation(_Transform.Rotation);

	UPhysicsComponent* PhysicsComponent = Instigator->GetComponentByClass<UPhysicsComponent>();
	if (PhysicsComponent)
	{
		FVector3 Velocity = PhysicsComponent->GetVelocity();

		if (Velocity.x >= -4.0f)
			PhysicsComponent->SetXVelocity(-4.0f);
	}

	URenderComponent* RenderComponent = Instigator->GetComponentByClass<URenderComponent>();
	if (RenderComponent)
	{
		RenderComponent->SetCurrentAnimation(EAnimationName::Walk);
	}
}
