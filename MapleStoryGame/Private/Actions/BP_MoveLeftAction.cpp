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
	FTransform _Transform = Instigator->GetTransform();
	_Transform.Rotation.y = 0;
	Instigator->SetRotation(_Transform.Rotation);

	UPhysicsComponent* PhysicsComponent = Instigator->GetComponentByClass<UPhysicsComponent>();
	if (PhysicsComponent)
		PhysicsComponent->SetXVelocity(-300.0f);

	URenderComponent* RenderComponent = Instigator->GetComponentByClass<URenderComponent>();
	if (RenderComponent)
	{
		RenderComponent->SetCurrentAnimation(EAnimationName::Walk);
	}
}
