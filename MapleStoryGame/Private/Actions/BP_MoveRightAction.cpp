#include "GamePch.h"
#include "Actions/BP_MoveRightAction.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "Actor/Actor.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "RenderCore/RenderComponent.h"

BP_MoveRightAction::BP_MoveRightAction()
{
	Tag = GameplayTagsManager->FindRegisteredTagExact("Action.MoveRight");
}

void BP_MoveRightAction::StartAction(AActor* Instigator)
{
	FTransform _Transform = Instigator->GetTransform();
	_Transform.Rotation.y = 180;
	Instigator->SetRotation(_Transform.Rotation);

	UPhysicsComponent* PhysicsComponent = Instigator->GetComponentByClass<UPhysicsComponent>();
	if (PhysicsComponent)
		PhysicsComponent->SetXVelocity(300.0f);

	URenderComponent* RenderComponent = Instigator->GetComponentByClass<URenderComponent>();
	if (RenderComponent)
	{
		RenderComponent->SetCurrentAnimation(EAnimationName::Walk);
	}
}
